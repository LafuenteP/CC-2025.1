//-----------------------

//Usando 3ds

//Model3DS carro = Model3DS("../3ds/cartest.3DS");

//    glTranslatef(1,1,0);
//    GUI::drawOrigin(0.5);
//    glScalef(1,1,0.5);
//    glRotatef(-90, 1,0,0);
//    glTranslatef(0,0,0);
//    glScalef(0.0005,0.0005,0.0005);
//    carro.draw();

//void desenha() {
//    GUI::draw3ds(*model,x,0,z,0,90+angY,0);
//}

//void GUI::draw3ds(Model3DS &model3DS, float tx, float ty, float tz,
//                                      float ax, float ay, float az,
//                                      float sx, float sy, float sz)
//{
//    glPushMatrix();
//        //transformacoes do objeto ja desenhado de acordo com o seu sistema local
//        glTranslatef(tx,ty,tz);
//        glRotatef(ax,1,0,0);
//        glRotatef(ay,0,1,0);
//        glRotatef(az,0,0,1);
//        glScalef(sx,sy,sz);
//        //sist local
//        //drawOrigin(0.5);
//        //desfazendo as transformações usadas na hora da modelagem
//        //trazendo para a origem, alinhando com os eixos locais e ajustando para um tamanho adequado (Sl.Rl.Tl)
//        glScalef(1,1,1);
//        glRotatef(-90, 1,0,0);
//        glTranslatef(0,0,0);
//        //primeiro aplica uma escala para que o objeto fique visível adequadamente no cenário
//        float s = 0.0005;
//        glScalef(s,s,s);
//        model3DS.draw();
//    glPopMatrix();
//}

//-----------------------

//Usando texturas

//GUI::habilitaTextura(true,false,0);
//GUI::selecionaTextura(id);

//objeto a ser desenhado

//GUI::desabilitaTextura(true,false);


//-----------------------

//Usando planos de corte

if (drawCubo2x2x2) {
    //clipping
    GLdouble planes[6][4] = { { 1.0, 0.0, 0.0, 1},
                              {-1.0, 0.0, 0.0, 1},
          //comentario errado { 0.0, 1.0, 0.0, 1}, //deixa o y positivo aparecendo (a partir do y=1) (corta o y<1)
           /*(corta o y<-1)*/ { 0.0, 1.0, 0.0, 1}, //deixa a parte acima (y) do plano aparecendo (plano posicionado no y=-1, d desloca o plano no sentido oposto à normal)
                              { 0.0,-1.0, 0.0, 1},
                              { 0.0, 0.0, 1.0, 1},
                              { 0.0, 0.0,-1.0, 1} };
    for (int pl=0;pl<6;pl++) {
        glClipPlane(GL_CLIP_PLANE0+pl, planes[pl]);
        glEnable(GL_CLIP_PLANE0+pl);
    }

    //objeto a ser desenhado

    //clipping
    for (int pl=0;pl<6;pl++) {
        glDisable(GL_CLIP_PLANE0+pl);
    }
}

    //GUI::drawSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    GUI::drawHalfSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    GUI::drawSphereInsideBox222(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);

//-----------------------

//Testando implementar transformacoes sem usar matrizes

//Vetor3D rotacaoZ( Vetor3D v, float theta ) {
//    Vetor3D vt;
//    float thetaRad = theta*PI/180;
//    vt.x = cos(thetaRad)*v.x - sin(thetaRad)*v.y;
//    vt.y = sin(thetaRad)*v.x + cos(thetaRad)*v.y;
//    vt.z = v.z;
//    return vt;
//}

//Vetor3D translacao( Vetor3D v, Vetor3D desl ) {
//    Vetor3D vt;
//    vt.x = v.x + desl.x;
//    vt.y = v.y + desl.y;
//    vt.z = v.z + desl.z;
//    return vt;
//}

//void transformacoesSemMatriz() {
//    //testando transformar um objeto (um simples triangulo, por exemplo)

//    //translacao
//    //glBegin(GL_POLYGON);
//    //    glNormal3f(0,0,1);
//    //    glVertex3f( 0+px,0+py, 0);
//    //    glVertex3f( 1+px,0+py, 0);
//    //    glVertex3f( 0+px,1+py, 0);
//    //glEnd();

//    //rotacao
//    // //theta += 1;
//    //float thetaRad = theta*PI/180;
//    //glBegin(GL_POLYGON);
//    //    glNormal3f(0,0,1);
//    //    //glVertex3f( 0,0, 0);
//    //    glVertex3f( cos(thetaRad)*0 - sin(thetaRad)*0, sin(thetaRad)*0 + cos(thetaRad)*0, 0);
//    //    //glVertex3f( 1,0, 0);
//    //    glVertex3f( cos(thetaRad)*1 - sin(thetaRad)*0, sin(thetaRad)*1 + cos(thetaRad)*0, 0);
//    //    //glVertex3f( 0,1, 0);
//    //    glVertex3f( cos(thetaRad)*0 - sin(thetaRad)*1, sin(thetaRad)*0 + cos(thetaRad)*1, 0);
//    //glEnd();

//    //aplicando funcoes de transformacao nos vertices do objeto

//    //exemplo de um triangulo 2D
//    //Vetor3D v1 = Vetor3D(0,0,0);
//    //Vetor3D v2 = Vetor3D(1,0,0);
//    //Vetor3D v3 = Vetor3D(0,1,0);

//    //exemplo de um objeto afastado da origem
//    //Vetor3D v1 = Vetor3D(1,0,0);
//    //Vetor3D v2 = Vetor3D(2,0,0);
//    //Vetor3D v3 = Vetor3D(1.5,1,0);

//    //exemplo guardando tbm o vetor normal do triangulo
//    //Vetor3D vN = Vetor3D(0,0,1);
//    //Vetor3D v1 = Vetor3D(0,0,0);
//    //Vetor3D v2 = Vetor3D(1,0,0);
//    //Vetor3D v3 = Vetor3D(0,1,0);

//    //exemplo da face frontal da nossa piramide
//    Vetor3D vN = Vetor3D(0,1,1);
//    Vetor3D v1 = Vetor3D(1,0,1);
//    Vetor3D v2 = Vetor3D(0,1,0);
//    Vetor3D v3 = Vetor3D(-1,0,1);

//    Vetor3D desl = Vetor3D( px,py,0 ); //          R.(T.vi)
//    v1 = translacao(v1,desl);
//    v2 = translacao(v2,desl);
//    v3 = translacao(v3,desl);

//    vN = rotacaoZ(vN,theta);
//    v1 = rotacaoZ(v1,theta);
//    v2 = rotacaoZ(v2,theta);
//    v3 = rotacaoZ(v3,theta);

//    glBegin(GL_POLYGON);
//        glNormal3f( vN.x, vN.y, vN.z );
//        glVertex3f( v1.x, v1.y, v1.z );
//        glVertex3f( v2.x, v2.y, v2.z );
//        glVertex3f( v3.x, v3.y, v3.z );
//    glEnd();
//}

//-----------------------

//Tarefas que identifiquei que estavam pendentes em alguma das aulas iniciais de um dos semestres anteriores

//adicionar:
//-deslocar cubo com o teclado
//-deslocar cubo com o mouse
//-primitivas OpenGL (glBegin, glEnd)
//-glNormal, iluminação

//-leitor 3DS
//-usar as transformacoes matriciais do proprio OpenGL
//-push/popMatrix (podem ser usados um dentro do outro - nocao de pilha)

//-ordem das transformacoes
//  -translacao e rotacao
//  -testar escala!!!
//-interpretacao de uma composicao de transformacoes já definida
//      <----------- globais
//  -   T.Rz.Ry.Rx.S . v
//      -----------> locais
//  -direita->esquerda: Transfs globais
//  -esquerda->direita: Transfs locais

//-----------------------









#include <iostream>

using namespace std;

#include <gui.h>
#include <vector>

Model3DS modeloCarro = Model3DS("../3ds/cartest.3DS");

float px = 2.0;
float py = 1.5;


void desenha() {
    GUI::displayInit();

    GUI::setLight(1,0,3,0,true,false);

    GUI::drawOrigin(1);

    GUI::setColor(1,0,0);
    GUI::drawFloor();

    GUI::setColor(0,1,0);
    GUI::drawSphere(px,py,0,0.2);
    //px += 0.01;


    GUI::displayEnd();
}

int sel = 0;

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {
    case 'J':
        px += 0.1;
        break;
    case 'j':
        px -= 0.1;
        break;
    case 'K':
        py += 0.1;
        break;
    case 'k':
        py -= 0.1;
        break;

    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    GUI gui = GUI(800,600,desenha,teclado);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}
