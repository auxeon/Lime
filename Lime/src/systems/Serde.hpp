#ifndef SERDE_H
#define SERDE_H


#include "Pch.hpp"
#include "components/TransformComponent.hpp";

extern Lime gLimeEngine;

namespace sdj {

    // example usage section
    struct vehicle {
        int carid;
        string carname;
    };

    struct person {
        string name;
        int age;
        vehicle car;
    };

    void to_json(json& j, const vehicle& x) {
        j = json{{"carid",x.carid},
                {"carname",x.carname}};
    }

    void from_json(const json& j, vehicle& x) {
        j.at("carid").get_to(x.carid);
        j.at("carname").get_to(x.carname);
    }

    void to_json(json& j, const person& x) {
        j = json{{"name", x.name},
                {"age", x.age},
                {"car",x.car}};
    }

    void from_json(const json& j, person& x) {
        j.at("name").get_to(x.name);
        j.at("age").get_to(x.age);
        j.at("car").get_to(x.car);
    }

    void to_json(json& j, const TransformComponent& x) {
        j = json{
            {"x",x.x},
            {"y",x.y},
            {"z",x.z}
            };
    }

    void from_json(const json& j, TransformComponent& x) {
        j.at("x").get_to(x.x);
        j.at("y").get_to(x.y);
        j.at("z").get_to(x.z);
    }



    void load(json& res, string filename= "pretty.json") {
        std::cout << "loading...\n";
        std::ifstream in(filename);
        in >> res;

    }

    void save(const json& res, string filename="pretty.json") {
        std::cout << "saving...\n";
        std::ofstream out(filename);
        out << std::setw(4) << res << std::endl;

    }

    void exampleloadsave() {

        // saving
        person p;
        p.name = "Abhikalp Unakal";
        p.age = 36;
        p.car.carid = 1;
        p.car.carname = "Audi";

        json res;
        to_json(res, p);
        save(res);


        // loading
        json j;
        load(j);
        person b;
        from_json(j, b);

        std::cout << "name : " << b.name << std::endl;
        std::cout << "age : " << b.age << std::endl;
        std::cout << "carid : " << b.car.carid << std::endl;
        std::cout << "carname : " << b.car.carname << std::endl;
    }

    void from_json(const json& j, Lime& x) {
        for (auto const& entity : j["entities"]) {
            auto ent = gLimeEngine.createEntity();
            for (auto const& comp : entity["components"]) {
                if (comp["ComponentID"] == 0) {
                    auto data = comp["ComponentData"];
                    gLimeEngine.addComponent(ent, TransformComponent{ data["x"],data["y"],data["z"] });
                }
            }

        }
    }

    void to_json(json& j, const Lime& x) {
        j = json{};
        for (const auto& entity : x.mEntityManager->mAllocdEntities) {
            json j0_0 = json{};
                j0_0["EntityID"] = entity;
                    json j0_1_0 = json{};
                    for (const auto& compTypePair : gLimeEngine.mComponentManager->mComponentTypes) {
                        auto compName = compTypePair.first;
                        auto compID = compTypePair.second;
                        // check if component exists
                        if (gLimeEngine.mEntityManager->hasComponent(entity, compID)) {
                            if (compID == 0) {
                                j0_1_0["ComponentID"] = compID;
                                j0_1_0["ComponentName"] = "TransformComponent";
                                auto& t = gLimeEngine.getComponent<TransformComponent>(entity);
                                to_json(j0_1_0["ComponentData"], t);
                            }
                        }
                    }
                j0_0["components"].push_back(j0_1_0);
            j["entities"].push_back(j0_0);
        }
    }

    void levelload(string filename) {
        //loading
        json j;
        load(j, filename);
        from_json(j, gLimeEngine);
        std::cout << std::setw(4) << j;
    }

    void levelsave(string filename) {
        //saving
        json res;
        to_json(res, gLimeEngine);
        save(res, filename);
        std::cout << std::setw(4) << res;
    }

    void levelloadsave() {
       
        levelsave("level.json");
        std::cout << std::endl;
        levelload("level.json");

    }

}



#endif // !SERDE_H
