#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"



Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }


    square->InitFromData(vertices, indices);
    return square;
}



Mesh* object2D::CreateLife(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3};

    

    square->SetDrawMode(GL_LINE_LOOP);

 

    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::CreateDeath(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);

    indices.push_back(3);

    square->SetDrawMode(GL_LINE_LOOP);



    square->InitFromData(vertices, indices);
    return square;
}


Mesh* object2D::CreateSquareOutline(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
    {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color)
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        square->SetDrawMode(GL_LINE_LOOP);


        square->InitFromData(vertices, indices);
        return square;
}


    Mesh* object2D::CreateRectangular(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float width,
        float height,
        glm::vec3 color,
        bool fill)
    {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(width, 0, 0), color),
            VertexFormat(corner + glm::vec3(width, height, 0), color),
            VertexFormat(corner + glm::vec3(0, height, 0), color)
        };

        Mesh* rect = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        if (!fill) {
            rect->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        rect->InitFromData(vertices, indices);
        return rect;
    }



    Mesh* object2D::CreateDiamond(
        const std::string& name,
        glm::vec3 center,
        float width,
        float height,
        glm::vec3 color,
        bool fill)
    {

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center + glm::vec3(0, width, 0), color),
            VertexFormat(center + glm::vec3(-height, 0, 0), color),
            VertexFormat(center + glm::vec3(0, -width, 0), color),
            VertexFormat(center + glm::vec3(height, 0, 0), color),

            VertexFormat(center + glm::vec3(width / 2, 0, 0), color),
            VertexFormat(center + glm::vec3(width * 1.1, height / 2, 0), color),
            VertexFormat(center + glm::vec3(width * 1.1, -height / 2, 0), color),

            //creare partea de aruncare a rombului

        };

        Mesh* diamond = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2,
                                             2, 3, 0,
                                             4, 5, 6,


        };



        diamond->InitFromData(vertices, indices);
        return diamond;
    }
    Mesh* object2D::CreateHexagon(
        const std::string& name,
        glm::vec3 center,
        float r,
        glm::vec3 color1,
        glm::vec3 color2,
        bool fill) 
    {
        //center = glm::vec3(0, 0, 0);

        std::vector<VertexFormat> vertices =
        {   VertexFormat(center,color2),
            VertexFormat(center + glm::vec3(r * cosf(RADIANS(0)), r * sin(RADIANS(0)), 0), color1),
            VertexFormat(center + glm::vec3(r * cosf(RADIANS(300)), r * sinf(RADIANS(300)), 0), color1),
            VertexFormat(center + glm::vec3(r * cosf(RADIANS(240)), r * sinf(RADIANS(240)),0), color1),
            VertexFormat(center + glm::vec3(r * cosf(RADIANS(180)), r * sinf(RADIANS(180)), 0), color1),
            VertexFormat(center + glm::vec3(r * cosf(RADIANS(120)), r * sinf(RADIANS(120)), 0), color1),
            VertexFormat(center + glm::vec3(r * cosf(RADIANS(60)), r * sinf(RADIANS(60)), 0), color1),

            VertexFormat(center + glm::vec3(r/2 * cosf(RADIANS(0)), r/2 * sin(RADIANS(0)), 1), color2),
            VertexFormat(center + glm::vec3(r/2 * cosf(RADIANS(300)), r/2 * sinf(RADIANS(300)), 1), color2),
            VertexFormat(center + glm::vec3(r/2 * cosf(RADIANS(240)), r/2 * sinf(RADIANS(240)),1), color2),
            VertexFormat(center + glm::vec3(r/2 * cosf(RADIANS(180)), r/2 * sinf(RADIANS(180)), 1), color2),
            VertexFormat(center + glm::vec3(r/2 * cosf(RADIANS(120)), r/2 * sinf(RADIANS(120)), 1), color2),
            VertexFormat(center + glm::vec3(r/2 * cosf(RADIANS(60)), r/2 * sinf(RADIANS(60)), 1), color2),

        };

        Mesh* hexagon = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2,
                                             0, 2, 3,
                                             0, 3, 4,
                                             0, 4, 5,
                                             0, 5, 6,
                                             0, 6, 1,

                                             0, 7, 8,
                                             0, 8, 9,
                                             0, 9, 10,
                                             0, 10, 11,
                                             0, 11, 12,
                                             0, 12, 7

        };
        hexagon->InitFromData(vertices, indices);
        return hexagon;

    }
    Mesh* object2D::CreateStar(
        const std::string& name,
        glm::vec3 center,
        float R,
        glm::vec3 color,
        bool fill) {

        std::vector<VertexFormat> vertices =
        {   VertexFormat(center,color),
            VertexFormat(center + glm::vec3(0,R, 1), color),
            VertexFormat(center + glm::vec3(R * cosf(RADIANS(18)),R * sinf(RADIANS(18)), 1), color),
            VertexFormat(center + glm::vec3(R * cosf(RADIANS(54)),R * sinf(RADIANS(-54)), 1), color),
            VertexFormat(center + glm::vec3(R * -cosf(RADIANS(54)),R * sinf(RADIANS(-54)),1), color),
            VertexFormat(center + glm::vec3(R * -cosf(RADIANS(18)),R * sinf(RADIANS(18)), 1), color),
            VertexFormat(center + glm::vec3(0,-R/2.5, 1), color),

        };


        Mesh* star = new Mesh(name);
        std::vector<unsigned int> indices = { 6,  1, 4,
                                              3, 1, 6,
                                              6, 2, 5


        };
        star->InitFromData(vertices, indices);
        return star;
    }
