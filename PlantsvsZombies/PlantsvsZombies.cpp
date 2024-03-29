#include "lab_m1/PlantsvsZombies/Tema.h"

#include <vector>
#include <iostream>

#include "lab_m1/PlantsvsZombies/transform2D.h"
#include "lab_m1/PlantsvsZombies/object2D.h"


using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

PlantsvsZombies::PlantsvsZombies()
{

}

PlantsvsZombies::~PlantsvsZombies()
{

}

void PlantsvsZombies::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	srand(time(0));

	squareSide = 100;
	outlineLength = 120;
	height_r = 320;
	width_r = 40;
	width_d = 30;
	height_d = 50;
	r = 40;
	angularStep = 0;
	nrLives = 3;
	nrStars = 8;

	glm::vec3 corner1 = glm::vec3(0, 0, 0);
	Mesh* dsquare = object2D::CreateSquare("dark_square", corner1, squareSide, glm::vec3(0.1, 0, 0.4), true);
	AddMeshToList(dsquare);

	glm::vec3 corner2 = glm::vec3(0, 0, 0);
	Mesh* lsquare = object2D::CreateSquare("light_square", corner2, squareSide, glm::vec3(0.2, 0, 0.5), true);
	AddMeshToList(lsquare);

	glm::vec3 corner3 = glm::vec3(0, 0, 0);
	Mesh* rectangular = object2D::CreateRectangular("rectangular", corner3, width_r, height_r, glm::vec3(0.2, 0, 0.6), true);
	AddMeshToList(rectangular);

	glm::vec3 corner4 = glm::vec3(0, 0, 0);
	Mesh* squareoutline = object2D::CreateSquareOutline("squareoutline", corner4, outlineLength, glm::vec3(0.2, 0, 0.6), true);
	AddMeshToList(squareoutline);

	glm::vec3 corner5 = glm::vec3(0, 0, 0);
	Mesh* life = object2D::CreateLife("life", corner5, outlineLength, glm::vec3(0.2, 0, 0.6), true);
	AddMeshToList(life);

	Mesh* death = object2D::CreateDeath("death", corner5, outlineLength, glm::vec3(0.2, 0, 0.6), true);
	AddMeshToList(death);

	glm::vec3 center1 = glm::vec3(0, 0, 1);
	Mesh* diamond1 = object2D::CreateDiamond("diamond1", center1, height_d, width_d, glm::vec3(0.69f, 0.078f, 0.137f), true);
	AddMeshToList(diamond1);

	glm::vec3 center2 = glm::vec3(0, 0, 1);
	Mesh* diamond2 = object2D::CreateDiamond("diamond2", center2, height_d, width_d, glm::vec3(0, 0, 1), true);
	AddMeshToList(diamond2);

	glm::vec3 center3 = glm::vec3(0, 0, 1);
	Mesh* diamond3 = object2D::CreateDiamond("diamond3", center3, height_d, width_d, glm::vec3(0.778f, 0.735f, 0.157f), true);
	AddMeshToList(diamond3);

	glm::vec3 center4 = glm::vec3(0, 0, 1);
	Mesh* diamond4 = object2D::CreateDiamond("diamond4", center4, height_d, width_d, glm::vec3(0, 0.6, 0.2), true);
	AddMeshToList(diamond4);

	glm::vec3 center5 = glm::vec3(0, 0, 1);
	Mesh* hexagon1 = object2D::CreateHexagon("hexagon1", center5, r, glm::vec3(0.51f, 0.051f, 0.075f), glm::vec3(0.69f, 0.078f, 0.137f), true);
	AddMeshToList(hexagon1);

	glm::vec3 center6 = glm::vec3(0, 0, 1);
	Mesh* hexagon2 = object2D::CreateHexagon("hexagon2", center6, r, glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 1), true);
	AddMeshToList(hexagon2);

	glm::vec3 center7 = glm::vec3(0, 0, 1);
	Mesh* hexagon3 = object2D::CreateHexagon("hexagon3", center7, r, glm::vec3(1, 0.986f, 0), glm::vec3(0.778f, 0.735f, 0.157f), true);
	AddMeshToList(hexagon3);

	glm::vec3 center8 = glm::vec3(0, 0, 1);
	Mesh* hexagon4 = object2D::CreateHexagon("hexagon4", center8, r, glm::vec3(0, 0.4, 0.1), glm::vec3(0, 0.6, 0.2), true);
	AddMeshToList(hexagon4);

	glm::vec3 center9 = glm::vec3(0, 0, 1);
	Mesh* bullet1 = object2D::CreateStar("bullet1", center9, r, glm::vec3(0.69f, 0.078f, 0.137f), true);
	AddMeshToList(bullet1);

	Mesh* bullet2 = object2D::CreateStar("bullet2", center9, r, glm::vec3(0, 0, 1), true);
	AddMeshToList(bullet2);

	Mesh* bullet3 = object2D::CreateStar("bullet3", center9, r, glm::vec3(0.778f, 0.735f, 0.157f), true);
	AddMeshToList(bullet3);

	Mesh* bullet4 = object2D::CreateStar("bullet4", center9, r, glm::vec3(0, 0.6, 0.2), true);
	AddMeshToList(bullet4);

	Mesh* star = object2D::CreateStar("star", center9, r, glm::vec3(0.396f, 0.078f, 0.459f), true);
	AddMeshToList(star);

}

void PlantsvsZombies::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void PlantsvsZombies::Update(float deltaTimeSeconds)
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(500, 500);
	if (!nrLives)
		Exit(); // game over

	modelMatrix = glm::mat3(1); // Resetam matricea model 
	for (int i = 1; i < 8; i += 2) { // creez tabla, alternand culoriile patratelor
		modelMatrix *= transform2D::Translate(resolution.x - i * squareSide - 10, 10);
		RenderMesh2D(meshes["dark_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, squareSide + 10);
		RenderMesh2D(meshes["light_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, squareSide + 10);
		RenderMesh2D(meshes["dark_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);

		modelMatrix *= transform2D::Translate(resolution.x - (i + 1) * squareSide - 10, 10);
		RenderMesh2D(meshes["light_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, squareSide + 10);
		RenderMesh2D(meshes["dark_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, squareSide + 10);
		RenderMesh2D(meshes["light_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
	}
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(10, 10);
	RenderMesh2D(meshes["rectangular"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);

	for (int i = 0; i < 3; i++) {
		modelMatrix *= transform2D::Translate(width_r + 20 + 20 * i + squareSide * i, 10);
		RenderMesh2D(meshes["dark_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, squareSide + 10);
		RenderMesh2D(meshes["dark_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, squareSide + 10);
		RenderMesh2D(meshes["dark_square"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(outlineLength, resolution.y - outlineLength - 30);
	RenderMesh2D(meshes["squareoutline"], shaders["VertexColor"], modelMatrix);

	for (int i = 2; i < 5; i++) { // create the square outlines for the diamonds
		modelMatrix *= transform2D::Translate(outlineLength * 1.5, 0);
		RenderMesh2D(meshes["squareoutline"], shaders["VertexColor"], modelMatrix);
	}

	modelMatrix *= transform2D::Translate(outlineLength / 2, outlineLength / 2);
	RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= transform2D::Translate(-1.5 * outlineLength, 0);
	RenderMesh2D(meshes["diamond2"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= transform2D::Translate(-1.5 * outlineLength, 0);
	RenderMesh2D(meshes["diamond3"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= transform2D::Translate(-1.5 * outlineLength, 0);
	RenderMesh2D(meshes["diamond4"], shaders["VertexColor"], modelMatrix);


	// DIAMONDS 
	if (!Diamonds.empty())
		for (float i = 0; i < Diamonds.size(); i++)
		{
			modelMatrix = glm::mat3(1); // we minimize the star if the player right clicked
			modelMatrix *= transform2D::Translate(Diamonds[i]->coord.first, Diamonds[i]->coord.second);
			if (Diamonds[i]->scale) {
				if (Diamonds[i]->scaleStep > 0) {
					Diamonds[i]->scaleStep -= deltaTimeSeconds;
					modelMatrix *= transform2D::Scale(Diamonds[i]->scaleStep, Diamonds[i]->scaleStep);
				}
				if (Diamonds[i]->scaleStep < 0) {
					Diamonds[i]->id = -2; // we make sure it disappears in the end
				}
			}
			if (Diamonds[i]->id == 4)
				RenderMesh2D(meshes["diamond4"], shaders["VertexColor"], modelMatrix);
			else if (Diamonds[i]->id == 3)
				RenderMesh2D(meshes["diamond3"], shaders["VertexColor"], modelMatrix);
			else if (Diamonds[i]->id == 2)
				RenderMesh2D(meshes["diamond2"], shaders["VertexColor"], modelMatrix);
			else if (Diamonds[i]->id == 1)
				RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);
		}

	// we make sure the diamonds disappear if they've been hit by hexagons
	for (float i = 0; i < Diamonds.size(); i++)
		for (float j = 0; j < Hexagons.size(); j++)
		{
			float distanceR = glm::distance(glm::vec2((Diamonds[i]->coord.first), Diamonds[i]->coord.second), glm::vec2((Hexagons[j]->coord.first), Hexagons[j]->coord.second));
			// collision diamond hexagon
			if (distanceR < Diamonds[i]->radius + Hexagons[j]->radius)
				if ( Hexagons[j]->render && Diamonds[i]->render)
				Diamonds[i]->scale = true;
		}

	//HEXAGONS
	angularStep += deltaTimeSeconds;
	for (float i = 0; i < Hexagons.size(); i++)
		if (Hexagons[i]->render)
		{
			Hexagons[i]->coord.first -= 100 * deltaTimeSeconds;
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(Hexagons[i]->coord.first, Hexagons[i]->coord.second);
			modelMatrix *= transform2D::Rotate(angularStep);
			int a = Hexagons[i]->id;
			RenderMesh2D(meshes["hexagon" + std::to_string(a)], shaders["VertexColor"], modelMatrix);

			if (Hexagons[i]->coord.first < 0 && Hexagons[i]->render) {
				Hexagons[i]->render = false; //when a hexagons passes by, life lost
				nrLives--;
			}
			if (Hexagons[i]->hit == 3)
				Hexagons[i]->render = false; // when a hexagon is hit tree times, it disappears
		}
	random1 = rand() % 550;
	if (random1 == 10) {
		random2 = (rand() % 3);
		randomid = (rand() % 4) + 1;
		h = new Hexa(randomid, true, r, false, 1, 0, { resolution.x - 10,  15 * random2 + squareSide / 2 + squareSide * random2 });
		Hexagons.push_back(h);
	}


	// STARS
	random3 = rand() % 500; // rendering the stars that pop un on screen
	if (random3 == 10) {
		x = rand() % resolution.x;
		y = rand() % resolution.y;
		s = new Star(0, true, r, { x,y });
		Stars.push_back(s);
	}
	for (float i = 0; i < Stars.size(); i++)
		if (Stars[i]->render)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(Stars[i]->coord.first, Stars[i]->coord.second);
			RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
		}
	for (float i = 1, j = 1; i < 6 && j < 5; i += 1.5f, j++)  // rendering the prices for the diamonds
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(i * outlineLength + 15, resolution.y - outlineLength - 50);
		modelMatrix *= transform2D::Scale(0.35, 0.35);
		RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
		for (int k = 1; k < j; k++) {
			modelMatrix *= transform2D::Translate(r * 2, 0);
			RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
		}
	}
	for (float i = 0; i < nrStars; i++) // we add the points/stars we get
	{
		modelMatrix = glm::mat3(1);
		if (i >= 64) // we align them line by line
			return;
		if (i > 48)
			modelMatrix *= transform2D::Translate(resolution.x - outlineLength * 3.5 + r / 2 * (i - 48), resolution.y - outlineLength - 50 - r / 2 * 3);
		else if (i >= 32)
			modelMatrix *= transform2D::Translate(resolution.x - outlineLength * 3.5 + r / 2 * (i - 32), resolution.y - outlineLength - 50 - r / 2 * 2);
		else if (i > 16)
			modelMatrix *= transform2D::Translate(resolution.x - outlineLength * 3.5 + r / 2 * (i - 16), resolution.y - outlineLength - 50 - r / 2);
		else
			modelMatrix *= transform2D::Translate(resolution.x - outlineLength * 3.5 + r / 2 * i, resolution.y - outlineLength - 50);

		modelMatrix *= transform2D::Scale(0.25, 0.25);
		RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
	}

	//  BULLETS
	for (int i = 0; i < Hexagons.size(); i++)
		for (int j = 0; j < Diamonds.size(); j++) // trying to start the right bullets
		{
			if (Hexagons[i]->render)
				if (abs(Diamonds[j]->coord.second - Hexagons[i]->coord.second) < 20)
					if (Diamonds[j]->id == Hexagons[i]->id)
						if (Diamonds[j]->render)
							Diamonds[j]->waitTime -= deltaTimeSeconds;

			if (Diamonds[j]->waitTime < 0) {
				Diamonds[j]->waitTime = 2; // we wait 2 sec before starting new bullet
				b = new Bullet(Diamonds[j]->id, true, r, { Diamonds[j]->coord.first,  Diamonds[j]->coord.second }); // we create bullets anytime we create a diamond
				Bullets.push_back(b);
			}
		}

	for (int i = 0; i < Hexagons.size(); i++)
		for (int j = 0; j < Bullets.size(); j++) {
			float distanceR = glm::distance(glm::vec2((Bullets[j]->coord.first), Bullets[j]->coord.second), glm::vec2((Hexagons[i]->coord.first), Hexagons[i]->coord.second));
			//collision bullet hexagon
			if (distanceR < Bullets[j]->radius + Hexagons[i]->radius / 2)
				if (Bullets[j]->render && Hexagons[i]->render) // we make sure to hit only the correct hexagons
					if (Bullets[j]->id == Hexagons[i]->id)
					{
						Bullets[j]->render = false;
						Hexagons[i]->hit++;
					}
		}

	for (float i = 0; i < Bullets.size(); i++)
		if (Bullets[i]->render)
		{
			Bullets[i]->coord.first += 200 * deltaTimeSeconds;
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(Bullets[i]->coord.first, Bullets[i]->coord.second);
			modelMatrix *= transform2D::Rotate(angularStep);
			if (Bullets[i]->id == 4)
				RenderMesh2D(meshes["bullet4"], shaders["VertexColor"], modelMatrix);
			else if (Bullets[i]->id == 3)
				RenderMesh2D(meshes["bullet3"], shaders["VertexColor"], modelMatrix);
			else if (Bullets[i]->id == 2)
				RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], modelMatrix);
			else if (Bullets[i]->id == 1)
				RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], modelMatrix);
		}
	// LIVES
	modelMatrix = glm::mat3(1); // reset the matrix
	modelMatrix *= transform2D::Translate(resolution.x - 3.5 * outlineLength, resolution.y - outlineLength - 30);
	if (nrLives > 2)
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["death"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(resolution.x - 2.5 * outlineLength, resolution.y - outlineLength - 30);
	if (nrLives > 1)
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["death"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(resolution.x - 1.5 * outlineLength, resolution.y - outlineLength - 30);
	if (nrLives > 0)
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["death"], shaders["VertexColor"], modelMatrix);


}

void PlantsvsZombies::FrameEnd()
{
	//DrawCoordinateSystem();
}

void PlantsvsZombies::OnInputUpdate(float deltaTime, int mods)
{
	// Add smth
}

void PlantsvsZombies::OnKeyPress(int key, int mods)
{
	// Add key press event
}

void PlantsvsZombies::OnKeyRelease(int key, int mods)
{
	// Add key release event
}

void PlantsvsZombies::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	sceneY = 720 - mouseY;
	if (!Diamonds.empty())
		for (int i = 0; i < Diamonds.size(); i++)
		{
			if (!Diamonds[i]->render) {
				Diamonds[i]->coord.first = mouseX;
				Diamonds[i]->coord.second = sceneY;
			}
		}
}

void PlantsvsZombies::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	sceneY = 720 - mouseY;
	if (button == 1) { // if left click on diamond then drag
		for (float i = 1, j = 4; i < 6 && j > 0; i += 1.5, j--) // anytime i drag a new diamond
			if (mouseX > outlineLength * i && mouseX < outlineLength * (i + 1))
				if (sceneY > resolution.y - outlineLength - 30 && sceneY < resolution.y - 30)
				{
					d = new Diam(j, false, width_d, false, 1, 0, 0, { mouseX,sceneY });
					Diamonds.push_back(d);
				}
		for (int i = 0; i < Stars.size(); i++) // when we press a star we increment our points
			if (Stars[i]->render)
				if (mouseX > Stars[i]->coord.first - Stars[i]->radius && mouseX < Stars[i]->coord.first + Stars[i]->radius)
					if (sceneY > Stars[i]->coord.second - Stars[i]->radius && sceneY < Stars[i]->coord.second + Stars[i]->radius)
					{
						nrStars++;
						Stars[i]->render = false;
					}
	}
	if (button == 2) // if right clicked on diamond then disappear
		for (int i = 0; i < Diamonds.size(); i++)
			if (Diamonds[i]->render)
				if (mouseX > Diamonds[i]->coord.first - squareSide / 2 && mouseX < Diamonds[i]->coord.first + squareSide / 2)
					if (sceneY > Diamonds[i]->coord.second - squareSide / 2 && sceneY < Diamonds[i]->coord.second + squareSide / 2)
						Diamonds[i]->scale = true;
}

void PlantsvsZombies::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	sceneY = 720 - mouseY;
	if (!Diamonds.empty())
		for (int i = 0; i < Diamonds.size(); i++) {
			for (int j = 0; j < 3; j++)
				if (mouseX > width_r + (j + 1) * 20 + squareSide * j && mouseX < (j + 1) * squareSide + width_r + (j + 1) * 20) { // check if the diamand is dropped right
					if (sceneY < squareSide + 10 && sceneY > 10 && (!Diamonds[i]->render))
					{
						Diamonds[i]->coord.first = squareSide / 2 + squareSide * j + width_r + 15 * (j + 1);
						Diamonds[i]->coord.second = 10 + squareSide / 2;
						if (nrStars >= 5 - Diamonds[i]->id) // we check if we can afford the diamond
						{
							Diamonds[i]->render = true;

						}
						if (Diamonds[i]->id == 4 && nrStars >= 1)
							nrStars--;
						else if (Diamonds[i]->id == 3 && nrStars >= 2) {
							for (int i = 0; i < 2; i++)
								nrStars--;

						}
						else if (Diamonds[i]->id == 2 && nrStars >= 3) {
							for (int i = 0; i < 3; i++)
								nrStars--;
						}
						else if (Diamonds[i]->id == 1 && nrStars >= 4)
							for (int i = 0; i < 4; i++)
								nrStars--;

					}
					else if (sceneY < 2 * squareSide + 20 && sceneY > squareSide + 20 && (!Diamonds[i]->render))
					{
						Diamonds[i]->coord.first = squareSide / 2 + squareSide * j + width_r + 15 * (j + 1);
						Diamonds[i]->coord.second = 20 + squareSide + squareSide / 2;
						if (nrStars >= 5 - Diamonds[i]->id) // we check if we can afford the diamond
						{
							Diamonds[i]->render = true;
						}
						if (Diamonds[i]->id == 4 && nrStars >= 1)
							nrStars--;
						else if (Diamonds[i]->id == 3 && nrStars >= 2) {
							for (int i = 0; i < 2; i++)
								nrStars--;

						}
						else if (Diamonds[i]->id == 2 && nrStars >= 3) {
							for (int i = 0; i < 3; i++)
								nrStars--;
						}
						else if (Diamonds[i]->id == 1 && nrStars >= 4)
							for (int i = 0; i < 4; i++)
								nrStars--;
					}
					else if (sceneY < 3 * squareSide + 30 && sceneY > 2 * squareSide + 30 && (!Diamonds[i]->render))
					{
						Diamonds[i]->coord.first = squareSide / 2 + squareSide * j + width_r + 15 * (j + 1);
						Diamonds[i]->coord.second = 30 + squareSide * 2 + squareSide / 2;
						if (nrStars >= 5 - Diamonds[i]->id) // we check if we can afford the diamond
						{
							Diamonds[i]->render = true;
						}
						if (Diamonds[i]->id == 4 && nrStars >= 1)
							nrStars--;
						else if (Diamonds[i]->id == 3 && nrStars >= 2) {
							for (int i = 0; i < 2; i++)
								nrStars--;

						}
						else if (Diamonds[i]->id == 2 && nrStars >= 3) {
							for (int i = 0; i < 3; i++)
								nrStars--;
						}
						else if (Diamonds[i]->id == 1 && nrStars >= 4)
							for (int i = 0; i < 4; i++)
								nrStars--;
					}
				}
			if (!Diamonds[i]->render) // if the diamand is dropped in a random wrong place
				Diamonds[i]->id = -1; // it shouldn't be rendered in the update function
		}
}


void PlantsvsZombies::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void PlantsvsZombies::OnWindowResize(int width, int height)
{
}
