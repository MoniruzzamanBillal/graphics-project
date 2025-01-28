#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <vector>
#include <iostream>  // For debugging

// Data structures
struct Mosquito
{
    float x, y;
    bool isWingUp, isAlive;
};
struct Egg
{
    float x, y;
};
struct Spray
{
    float x, y;
};

Mosquito mosquito = {0.0f, 0.0f, true, true};
std::vector<Egg> eggs;
Spray spray = {0.0f, -0.8f};
bool isContainerFull = true;
int currentScene = 1; // Scene 1: Initial, Scene 2: Water container, Scene 3: Spray and mosquito


// Draw text function
void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    while (*text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
}

// Draw mosquito
void drawMosquito()
{
    if (!mosquito.isAlive) return;
    glPushMatrix();
    glTranslatef(mosquito.x, mosquito.y, 0);

    // Body and head
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.05, 20, 20);
    glTranslatef(0.08f, 0.0f, 0);
    glutSolidSphere(0.03, 20, 20);

    // Wings
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);
    float offset = mosquito.isWingUp ? 0.15f : 0.10f;
    glVertex2f(-0.05f, 0.05f);
    glVertex2f(-0.15f, offset);
    glVertex2f(-0.05f, offset);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(-0.15f, -offset);
    glVertex2f(-0.05f, -offset);
    glEnd();

    glPopMatrix();
}

// Draw eggs
void drawEggs()
{
    glColor3f(0.8f, 0.6f, 0.4f);
    for (const auto& egg : eggs)
    {
        glPushMatrix();
        glTranslatef(egg.x, egg.y, 0);
        glutSolidSphere(0.02, 10, 10);
        glPopMatrix();
    }
}

// Draw water container
void drawWaterContainer()
{
    glColor3f(0.6f, 0.4f, 0.2f);
    glPushMatrix();
    glTranslatef(0.6f, -0.6f, 0);
    glScalef(0.35f, 0.3f, 2.0f); // Increase both width and height of the container
    glutSolidCube(1.0f);
    glPopMatrix();

    if (isContainerFull)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glPushMatrix();
        glTranslatef(0.6f, -0.58f, 0);
        glScalef(0.32f, 0.25f, 1.0f); // Adjust the water size to match the new container size
        glutSolidCube(1.0f);
        glPopMatrix();
        drawText(-0.05f, -0.8f, "Container is full with water.Mosquito can lay eggs.");
    }
    else
    {
        drawText(0.01f, -0.8f, "Container is empty! Mosquito can't lay eggs.");
    }
}

// Draw spray
void drawSpray()
{

  glColor3f(0.5f, 0.5f, 0.5f);
    drawText(spray.x - 0.06f, spray.y - 0.01f, "Spray");


    for (int i = 0; i < 10; ++i)
    {
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        glColor3f(0.2f, 0.2f, 0.2f);
        glPushMatrix();
        glTranslatef(spray.x + cos(angle) * 0.1f, spray.y + sin(angle) * 0.1f, 0);
        glutSolidSphere(0.01, 5, 5);
        glPopMatrix();
    }
}





// Draw a detailed house
void drawHouse(float x, float y)
{
    // Main house body
    glColor3f(1.0f, 0.6f, 0.2f); // Light orange
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(0.4f, 0.3f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Roof
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.2f, y + 0.15f);
    glVertex2f(x + 0.2f, y + 0.15f);
    glVertex2f(x, y + 0.35f);
    glEnd();

    // Door
    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glPushMatrix();
    glTranslatef(x, y - 0.1f, 0);
    glScalef(0.1f, 0.2f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Left Window
    glColor3f(0.5f, 0.8f, 1.0f); // Light blue
    glPushMatrix();
    glTranslatef(x - 0.1f, y + 0.05f, 0);
    glScalef(0.08f, 0.08f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Right Window
    glPushMatrix();
    glTranslatef(x + 0.1f, y + 0.05f, 0);
    glScalef(0.08f, 0.08f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Chimney
    glColor3f(0.5f, 0.3f, 0.2f); // Dark brown
    glPushMatrix();
    glTranslatef(x + 0.1f, y + 0.3f, 0);
    glScalef(0.05f, 0.2f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Add some grass (front yard)
    glColor3f(0.0f, 0.5f, 0.0f); // Green
    float grassOffsetY = -0.3f;
    glBegin(GL_QUADS);
    glVertex2f(x - 0.25f, y - 0.15f);
    glVertex2f(x + 0.25f, y - 0.15f);
    glVertex2f(x + 0.25f, y - 0.3f);
    glVertex2f(x - 0.25f, y - 0.3f);
    glEnd();
}





// Scene 1: Initial scene
void drawScene1()
{
    mosquito.isAlive = true;

       glColor3f(0.0f, 0.0f, 0.0f);


    drawText(-0.9f, 0.9f, "Welcome to Dengue Awareness!");
    drawText(-0.9f, 0.8f, "Press '2' to continue.");
    drawText(-0.9f, 0.7f, "-Dengue can cause high fever, severe pain, and even death!");
    drawText(-0.9f, 0.6f, "-Stay alert! Protect yourself from mosquito bites.");
    drawText(-0.9f, 0.5f, "-A single mosquito bite can spread the virus—take precautions!");
    drawText(-0.9f, 0.4f, "-prevention is key.");


    // House
    drawHouse(-0.7f, -0.5f);
    drawMosquito();

}

// Scene 2: Water container
void drawScene2()
{

 mosquito.isAlive = true;

       glColor3f(0.0f, 0.0f, 0.0f);


    drawText(-0.9f, 0.9f, "Scene 2: Water Container");
    drawText(-0.9f, 0.8f, "Press '3' to continue.");
    drawText(-0.9f, 0.7f, "-Press 'f' to fill, 'e' to empty the container.");
    drawText(-0.9f, 0.6f, "-Drag Mosquito into container and see result");
    drawText(-0.9f, 0.5f, "-Standing water = Mosquitoes' home!  ");
    drawText(-0.9f, 0.4f, "-Clean water containers, cover buckets, and remove stagnant water.  ");
    drawText(-0.9f, 0.3f, "-Mosquitoes lay eggs in just a few drops of water—stay vigilant.  ");
    drawText(-0.9f, 0.2f, "-Keep your surroundings dry and clean to reduce breeding grounds.  ");
    drawText(-0.9f, 0.1f, "-Even small plant saucers can collect water—empty them regularly.");
    drawWaterContainer();
    drawMosquito();
    drawEggs();
}

// Scene 3: Spray and mosquito
void drawScene3()
{


       glColor3f(0.0f, 0.0f, 0.0f);


    drawText(-0.9f, 0.9f, "Scene 3: Spray and Mosquito");
    drawText(-0.9f, 0.8f, "Use WASD to move spray and kill the mosquito.");
    drawText(-0.9f, 0.7f, "-Mosquitoes bite in the evening—stay safe! ");
    drawText(-0.9f, 0.6f, "-Use mosquito spray regularly, especially during dusk and dawn.");
    drawText(-0.9f, 0.5f, "-Spraying repellent in dark corners prevents mosquito hiding spots.");
    drawText(-0.9f, 0.4f, "-Apply spray near windows and doors to keep mosquitoes out.");
    drawText(-0.9f, 0.3f, "-Safe insect sprays can protect children and elderly individuals.");

    drawSpray();
    drawMosquito();
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScene == 1) drawScene1();
    else if (currentScene == 2) drawScene2();
    else if (currentScene == 3) drawScene3();

    glutSwapBuffers();
}




// Timer function to animate mosquito movement
void animateMosquito(int value)
{
    if (currentScene == 1 && mosquito.isAlive)
    {
        // Move the mosquito autonomously
        mosquito.x += (rand() % 3 - 1) * 0.05f; // Random movement (left, right, or stay)
        mosquito.y += (rand() % 3 - 1) * 0.05f; // Random movement (up, down, or stay)

        // Wrap mosquito around to the opposite side if it goes out of bounds
        if (mosquito.x > 1.0f) mosquito.x = -1.0f;
        if (mosquito.x < -1.0f) mosquito.x = 1.0f;
        if (mosquito.y > 1.0f) mosquito.y = -1.0f;
        if (mosquito.y < -1.0f) mosquito.y = 1.0f;
    }

    glutPostRedisplay(); // Redraw the scene after movement
    glutTimerFunc(100, animateMosquito, 0); // Call the function every 100 ms
}






// Handle mosquito movement and egg-laying
void handleSpecialInput(int key, int x, int y)
{


    if (currentScene == 3) // Only allow mosquito movement in Scene 1
    {
        // Move mosquito based on arrow keys
        if (key == GLUT_KEY_UP) mosquito.y += 0.05f;
        if (key == GLUT_KEY_DOWN) mosquito.y -= 0.05f;
        if (key == GLUT_KEY_LEFT) mosquito.x -= 0.05f;
        if (key == GLUT_KEY_RIGHT) mosquito.x += 0.05f;

        // Infinite movement behavior
        // Wrap mosquito around to the opposite side if it goes out of bounds
        if (mosquito.x > 1.0f) mosquito.x = -1.0f; // Wrap to the left side
        if (mosquito.x < -1.0f) mosquito.x = 1.0f; // Wrap to the right side
        if (mosquito.y > 1.0f) mosquito.y = -1.0f; // Wrap to the bottom
        if (mosquito.y < -1.0f) mosquito.y = 1.0f; // Wrap to the top

        glutPostRedisplay(); // Redraw the scene after movement
    }





    if (currentScene == 2) // Only allow mosquito movement in Scene 2
    {
        // Move mosquito based on arrow keys
        if (key == GLUT_KEY_UP) mosquito.y += 0.05f;
        if (key == GLUT_KEY_DOWN) mosquito.y -= 0.05f;
        if (key == GLUT_KEY_LEFT) mosquito.x -= 0.05f;
        if (key == GLUT_KEY_RIGHT) mosquito.x += 0.05f;

        // Ensure mosquito stays within screen bounds
        mosquito.x = std::max(-1.0f, std::min(1.0f, mosquito.x));
        mosquito.y = std::max(-1.0f, std::min(1.0f, mosquito.y));

        // Check if mosquito is near the container to lay eggs
        if (isContainerFull &&
                mosquito.x > 0.6f - 0.2f && mosquito.x < 0.6f + 0.2f &&  // Increased range
                mosquito.y > -0.6f - 0.2f && mosquito.y < -0.6f + 0.2f )
        {
            eggs.push_back({0.6f + (float)(rand() % 10 - 5) / 50.0f, -0.58f});

        }

        glutPostRedisplay(); // Redraw the scene after movement
    }
}

// Reset egg-laying flag when container is emptied
void handleKeyboard(unsigned char key, int x, int y)
{
    if (key == '1') currentScene = 1;
    else if (key == '2') currentScene = 2;
    else if (key == '3') currentScene = 3;
    else if (currentScene == 2)
    {
        if (key == 'f') isContainerFull = true;
        if (key == 'e')
        {
            isContainerFull = false;
            eggs.clear();

        }
    }
    else if (currentScene == 3)
    {
        if (key == 'w') spray.y += 0.05f;
        if (key == 's') spray.y -= 0.05f;
        if (key == 'a') spray.x -= 0.05f;
        if (key == 'd') spray.x += 0.05f;

        if (std::abs(spray.x - mosquito.x) < 0.1f && std::abs(spray.y - mosquito.y) < 0.1f) mosquito.isAlive = false;
    }

    glutPostRedisplay();
}

// Timer to animate mosquito wings
void animateWings(int value)
{
    mosquito.isWingUp = !mosquito.isWingUp;
    glutTimerFunc(100, animateWings, 0);
    glutPostRedisplay();
}

// Initialize OpenGL settings
void init()
{
    glClearColor(173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dengue Awareness Graphics");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleSpecialInput);
    glutTimerFunc(100, animateWings, 0);
    glutTimerFunc(100, animateMosquito, 0);

    glutMainLoop();
    return 0;
}


