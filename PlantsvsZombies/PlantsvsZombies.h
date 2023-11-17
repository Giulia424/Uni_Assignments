#pragma once

#include "components/simple_scene.h"

using namespace std;

namespace m1
{
    class PlantsvsZombies : public gfxc::SimpleScene
    {
    public:
        PlantsvsZombies();
        ~PlantsvsZombies();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleStep;
        float angularStep;
        float squareSide, height_r, width_r,height_d, width_d, outlineLength;
        float sceneY, sceneX;        
        float r;
        glm::ivec2 resolution;
        struct Diam
        {
            float id;
            bool render;
            float radius;
            bool scale;
            float scaleStep;
            float hit;
            float waitTime;
            std::pair<float, float> coord;  // coordinates for the drag and drop
            Diam(float nr, bool rend, float radius, bool scale, float scaleStep, float hit, float waitTime, pair<float, float > coord) : id(nr), render(rend), radius(radius),
                scale(scale), scaleStep(scaleStep), hit(hit), waitTime(waitTime), coord(coord) {
            }
            Diam() : id(), render(), radius(), scale(),scaleStep(), hit(), waitTime(), coord() {};

        };
        // the render value will be used to choose when the object is or not rendered
        vector<Diam*> Diamonds;
        Diam *d;

        struct Hexa
        {
            float id;
            bool render;
            float radius;
            bool scale;
            float scaleStep;
            float hit;
            std::pair<float, float> coord;  // coordinates for the drag and drop
            Hexa(float id, bool rend, float radius, bool scale, float scaleStep, float hit, pair<float, float > coord) : id(id),  render(rend), radius(radius),
                scale(scale), scaleStep(scaleStep), hit(hit), coord(coord) {
            }
            Hexa() : id(), render(), radius(), scale(), scaleStep(), hit(), coord() {};

        };
        
        Hexa* h;
        vector <Hexa*> Hexagons;

        struct Star
        {
            float id;
            bool render;
            float radius;
            std::pair<float, float> coord;  // coordinates for the drag and drop
            Star(float id, bool rend, float radius, pair<float, float > coord) : id(id), render(rend), radius(radius), coord(coord) {
            }
            Star() : id(), render(), radius(), coord() {};

        };

        Star* s;
        vector <Star*> Stars;


        struct Bullet
        {
            int id;
            bool render;
            float radius;
            std::pair<float, float> coord;  // coordinates for the drag and drop
            Bullet(float id,bool rend, float radius, pair<float, float > coord) : id(id), render(rend), radius(radius), coord(coord) {
            }
            Bullet() : id(), render(), radius(), coord() {};

        };

        Bullet* b;
        vector <Bullet*> Bullets;
       
        float random1, random2, random3, x, y;
        int randomid;
        float nrStars,nrLives;
        float distanceR;




    };
}   