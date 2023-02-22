#include <iostream>
#include <windows.h>
using namespace std;

char getCharAtxy(short int, short int);
void gotoxy(int, int);
void printMaze();
void printPlayer(int, int);
void erasePlayer(int, int);
void jump();
void moveLeft();
void moveRight();
void generateBullet();
void moveBullet();
void makeBulletInactive(int);
void printBullet(int, int);
void eraseBullet(int, int);
void gravity();
void addScore();
void printScore();
void printHorEnemy(int, int);
void eraseHorEnemy(int, int);
void printEnemy1Health();
void depleteHealth();
void bulletCollisionWithEnemy();
void generateEnemyBullet();
void moveHorEnemyBullet();
void makeEnemyBulletInactive(int);
void printEnemyBullet(int,int);
void bulletCollisionWithPlayer();
void playerHealth();
void chaserBee();
void printBee(int, int);
void printGhost(int, int);

bool restart = false;
int score = 0;
int timer = 0;
int timer1 = 0;

int playerX = 7;
int playerY = 19;
int health = 100;

int horizontalEnemy1X = 50;
int horizontalEnemy1Y = 19;
int horizontalEnemyHealth = 100;
int horEnemyBulletX[10000];
int horEnemyBulletY[10000];
bool isHorEnemyBulletActive[10000];

int smartBeeX = 40;
int smartBeeY = 3;

int verticalEnemy1X = 10;
int verticalEnemy1Y = 2;

int bulletX[10000];
int bulletY[10000];
bool isBulletActive[10000];

int bulletCount = 0;
int horEnemyBulletCount = 0;

main()
{
    system("cls");
    bool yes = false;
    bool alive = true;
    int gx=65, gy=2;
    int d1_flag = 1;
    printMaze();
    printPlayer(playerX, playerY);
    printHorEnemy(horizontalEnemy1X,horizontalEnemy1Y);
    printBee(smartBeeX, smartBeeY);
    while (true)
    {
        if(d1_flag == 1)
        {
            char nextSpot = getCharAtxy(gx,gy-1);
            if(nextSpot == '#')
            {
                d1_flag = 2;
            }
            else
            {
                eraseHorEnemy(gx,gy);
                if(nextSpot == 'M')
                {
                    break;
                }
                gy = gy - 1;
                printGhost(gx,gy);
            }
        }
        if(d1_flag == 2)
        {
            char nextSpot = getCharAtxy(gx,gy+1);
            if(nextSpot == '#')
            {
                d1_flag = 1;
            }
            else
            {
                eraseHorEnemy(gx,gy);
                if(nextSpot == 'M')
                {
                    break;
                }
                gy = gy + 1;
                printGhost(gx,gy);
            }
        }
        if(health <= 0)
        {
            break;
        }
        printScore();
        printEnemy1Health();
        playerHealth();
        yes = false;
        if(restart)
        {
            smartBeeX = 40;
            smartBeeY = 3;
            restart = false;
        }
        if(horizontalEnemyHealth = 0)
        {
            alive = false;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveRight();
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveLeft();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            yes = true;
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }
        if(alive)
        {
             if (timer == 15)
            {
                generateEnemyBullet();
                timer = 0;
            }
            moveHorEnemyBullet();
        }
        else
        {
            eraseHorEnemy(horizontalEnemy1X,horizontalEnemy1Y);
        }
        moveBullet();
        bulletCollisionWithEnemy();
        bulletCollisionWithPlayer();
        if(timer1 == 5)
        {
            chaserBee();
            timer1 = 0;
        }
        timer1++;
        timer++;
        if (yes)
        {
            jump();
        }
        gravity();
        Sleep(100);
    }
}

void bulletCollisionWithEnemy()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            if (bulletX[x] + 1 == horizontalEnemy1X && bulletY[x] == horizontalEnemy1Y)
            {
                addScore();
                depleteHealth();
            }
            if(bulletX[x] + 1 == smartBeeX && bulletY[x] == smartBeeY)
            {
                addScore();
                eraseHorEnemy(smartBeeX,smartBeeY);
                restart = true;
            }
        }
    }
}

void bulletCollisionWithPlayer()
{
    for (int x = 0; x < horEnemyBulletCount; x++)
    {
        if (isHorEnemyBulletActive[x] == true)
        {
            if (horEnemyBulletX[x] - 1 == playerX && horEnemyBulletY[x] == playerY)
            {
                health = health - 10;
            }
        }
    }
}

void depleteHealth()
{
    horizontalEnemyHealth = horizontalEnemyHealth - 10;
}

void printEnemy1Health()
{
    gotoxy(0,22);
    cout << "Enemy 1 Health=> " << horizontalEnemyHealth;
}

void gravity()
{
    char nextChar = getCharAtxy(playerX, playerY + 1);
    if (nextChar == ' ')
    {
        erasePlayer(playerX, playerY);
        playerY = playerY + 1;
        printPlayer(playerX, playerY);
    }
}

void generateEnemyBullet()
{
    char next = getCharAtxy(horizontalEnemy1X - 1, horizontalEnemy1Y);
    if (next == ' ')
    {
        horEnemyBulletX[horEnemyBulletCount] = horizontalEnemy1X - 1;
        horEnemyBulletY[horEnemyBulletCount] = horizontalEnemy1Y;
        isHorEnemyBulletActive[horEnemyBulletCount] = true;
        gotoxy(horizontalEnemy1X - 1, horizontalEnemy1Y);
        cout << "_";
        horEnemyBulletCount++;
    }
}

void moveHorEnemyBullet()
{
    for (int x = 0; x < horEnemyBulletCount; x++)
    {
        if (isHorEnemyBulletActive[x] == true)
        {
            char next = getCharAtxy(horEnemyBulletX[x] - 1, horEnemyBulletY[x]);
            if (next != ' ' || next == '.')
            {
                eraseBullet(horEnemyBulletX[x], horEnemyBulletY[x]);
                makeEnemyBulletInactive(x);
            }
            else
            {
                eraseBullet(horEnemyBulletX[x], horEnemyBulletY[x]);
                horEnemyBulletX[x] = horEnemyBulletX[x] - 1;
                printEnemyBullet(horEnemyBulletX[x], horEnemyBulletY[x]);
            }
        }
    }
}

void printEnemyBullet(int x, int y)
{
    gotoxy(x, y);
    cout << "_";
}

void moveBullet()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);
            if (next != ' ' || next == '_')
            {
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
            }
            else
            {
                eraseBullet(bulletX[x], bulletY[x]);
                bulletX[x] = bulletX[x] + 1;
                printBullet(bulletX[x], bulletY[x]);
            }
        }
    }
}

void printBullet(int x, int y)
{
    gotoxy(x, y);
    cout << ".";
}

void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void makeBulletInactive(int index)
{
    isBulletActive[index] = false;
}

void makeEnemyBulletInactive(int index)
{
    isHorEnemyBulletActive[index] = false;
}

void generateBullet()
{
    char next = getCharAtxy(playerX + 1, playerY);
    if (next == ' ')
    {
        bulletX[bulletCount] = playerX + 1;
        bulletY[bulletCount] = playerY;
        isBulletActive[bulletCount] = true;
        gotoxy(playerX + 1, playerY);
        cout << ".";
        bulletCount++;
    }
}

void moveRight()
{
    char nextChar;
    nextChar = getCharAtxy(playerX + 1, playerY);
    if (nextChar == ' ')
    {
        erasePlayer(playerX, playerY);
        playerX = playerX + 1;
        printPlayer(playerX, playerY);
    }
}

void moveLeft()
{
    char nextChar;
    nextChar = getCharAtxy(playerX - 1, playerY);
    if (nextChar == ' ')
    {
        erasePlayer(playerX, playerY);
        playerX = playerX - 1;
        printPlayer(playerX, playerY);
    }
}

void jump()
{
    int count = 0;
    char nextChar;
    for (int x = 1; x <= 5; x++)
    {
        nextChar = getCharAtxy(playerX, playerY - x);
        if (nextChar != ' ')
        {
            break;
        }
        count++;
    }
    char prevChar = getCharAtxy(playerX, playerY + 1);
    if (prevChar != ' ')
    {
        erasePlayer(playerX, playerY);
        playerY = playerY - count;
        printPlayer(playerX, playerY);
    }
}

void erasePlayer(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void printPlayer(int x, int y)
{
    gotoxy(x, y);
    cout << "M";
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void addScore()
{
    score++;
}

void printScore()
{
    gotoxy(0, 21);
    cout << "Score: " << score;
}

void printMaze()
{

    cout << "#########################################################################" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                      ******************               #" << endl;
    cout << "#                       *****                                           #" << endl;
    cout << "#          *******                                                      #" << endl;
    cout << "#                     **************                                    #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#                                     ************************          #" << endl;
    cout << "#             ***********************                                   #" << endl;
    cout << "#                                                                       #" << endl;
    cout << "#########################################################################" << endl;
}

void printHorEnemy(int x, int y)
{
    gotoxy(x,y);
    cout << "E";
}

void playerHealth()
{
    gotoxy(0,23);
    cout << "Player Health=> " << health;
}

void printBee(int x, int y)
{
    gotoxy(x,y);
    cout << "B";
}

void chaserBee()
{
    char nextSpot;
    if (playerX < smartBeeX)
        {
            nextSpot = getCharAtxy(smartBeeX - 1, smartBeeY);
            if (nextSpot != '#' && nextSpot != '*' && nextSpot != 'E')
            {
                eraseHorEnemy(smartBeeX,smartBeeY);
                if(nextSpot == 'M')
                {
                    restart = true;
                    health--;
                }
                smartBeeX = smartBeeX - 1;
                printBee(smartBeeX, smartBeeY);
            }
        }
        else if (playerX > smartBeeX)
        {
            nextSpot = getCharAtxy(smartBeeX + 1, smartBeeY);
            if (nextSpot != '#' && nextSpot != '*' && nextSpot != 'E')
            {
                eraseHorEnemy(smartBeeX,smartBeeY);
                if(nextSpot == 'M')
                {
                    restart = true;
                    health--;
                }
                smartBeeX = smartBeeX + 1;
                printBee(smartBeeX, smartBeeY);
            }
        }
        if (playerY < smartBeeY)
        {
            nextSpot = getCharAtxy(smartBeeX, smartBeeY - 1);
            if (nextSpot != '#' && nextSpot != '*' && nextSpot != 'E')
            {
                eraseHorEnemy(smartBeeX,smartBeeY);
                if(nextSpot == 'M')
                {
                    restart = true;
                    health--;
                }
                smartBeeY = smartBeeY - 1;
                printBee(smartBeeX, smartBeeY);
            }
        }
        else if (playerY > smartBeeY)
        {
            nextSpot = getCharAtxy(smartBeeX, smartBeeY + 1);
            if (nextSpot != '#' && nextSpot != '*' && nextSpot != 'E')
            {
                eraseHorEnemy(smartBeeX,smartBeeY);
                if(nextSpot == 'M')
                {
                    restart = true;
                    health--;
                }
                smartBeeY = smartBeeY + 1;
                printBee(smartBeeX, smartBeeY);
            }
        }
}

void printGhost(int x, int y)
{
    gotoxy(x,y);
    cout << "G";
}

void eraseHorEnemy(int x, int y)
{
    gotoxy(x,y);
    cout << " ";
}