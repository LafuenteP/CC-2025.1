#include <iostream>

using namespace std;

#include <gui.h>

float px = 0.0;
float py = 0.0;
float pz = 0.0;
float raio = 0.5;
float theta = 0.0;
//personagem
float thetaPelvis = 0.0;
float thetaTronco = 0.0;
float thetaBracoEsq = 0.0;
float thetaBracoDir = 0.0;

void piramide()
{
    //glBegin(GL_LINES);
    //    glVertex3f(0,0,0);
    //    glVertex3f(-1,1,0);
    //glEnd();
    //frontal
    glBegin(GL_POLYGON);
        glNormal3f(0,1,1);
        glVertex3f(1,0,1);
        glVertex3f(0,1,0);
        glVertex3f(-1,0,1);
    glEnd();
    //traseira
    glBegin(GL_POLYGON);
        glNormal3f(0,1,-1);
        glVertex3f(-1,0,-1);
        glVertex3f(0,1,0);
        glVertex3f(1,0,-1);
    glEnd();
    //lateral direita
    glBegin(GL_POLYGON);
        glNormal3f(1,1,0);
        glVertex3f(1,0,1);
        glVertex3f(1,0,-1);
        glVertex3f(0,1,0);
    glEnd();
    //lateral esquerda
    glBegin(GL_POLYGON);
        glNormal3f(-1,1,0);
        glVertex3f(-1,0,1);
        glVertex3f(0,1,0);
        glVertex3f(-1,0,-1);
    glEnd();
    //inferior
    glBegin(GL_POLYGON);
        glNormal3f(0,-1,0);
        glVertex3f( 1,0, 1);
        glVertex3f(-1,0, 1);
        glVertex3f(-1,0,-1);
        glVertex3f( 1,0,-1);
    glEnd();
}

Vetor3D rotacaoZ( Vetor3D v, float theta ) {
    Vetor3D vt;
    float thetaRad = theta*PI/180;
    vt.x = cos(thetaRad)*v.x - sin(thetaRad)*v.y;
    vt.y = sin(thetaRad)*v.x + cos(thetaRad)*v.y;
    vt.z = v.z;
    return vt;
}

Vetor3D translacao( Vetor3D v, Vetor3D desl ) {
    Vetor3D vt;
    vt.x = v.x + desl.x;
    vt.y = v.y + desl.y;
    vt.z = v.z + desl.z;
    return vt;
}

void transformacoesSemMatriz() {
    //testando transformar um objeto (um simples triangulo, por exemplo)

    //translacao
    //glBegin(GL_POLYGON);
    //    glNormal3f(0,0,1);
    //    glVertex3f( 0+px,0+py, 0);
    //    glVertex3f( 1+px,0+py, 0);
    //    glVertex3f( 0+px,1+py, 0);
    //glEnd();

    //rotacao
    // //theta += 1;
    //float thetaRad = theta*PI/180;
    //glBegin(GL_POLYGON);
    //    glNormal3f(0,0,1);
    //    //glVertex3f( 0,0, 0);
    //    glVertex3f( cos(thetaRad)*0 - sin(thetaRad)*0, sin(thetaRad)*0 + cos(thetaRad)*0, 0);
    //    //glVertex3f( 1,0, 0);
    //    glVertex3f( cos(thetaRad)*1 - sin(thetaRad)*0, sin(thetaRad)*1 + cos(thetaRad)*0, 0);
    //    //glVertex3f( 0,1, 0);
    //    glVertex3f( cos(thetaRad)*0 - sin(thetaRad)*1, sin(thetaRad)*0 + cos(thetaRad)*1, 0);
    //glEnd();

    //aplicando funcoes de transformacao nos vertices do objeto

    //exemplo de um triangulo 2D
    //Vetor3D v1 = Vetor3D(0,0,0);
    //Vetor3D v2 = Vetor3D(1,0,0);
    //Vetor3D v3 = Vetor3D(0,1,0);

    //exemplo de um objeto afastado da origem
    //Vetor3D v1 = Vetor3D(1,0,0);
    //Vetor3D v2 = Vetor3D(2,0,0);
    //Vetor3D v3 = Vetor3D(1.5,1,0);

    //exemplo guardando tbm o vetor normal do triangulo
    //Vetor3D vN = Vetor3D(0,0,1);
    //Vetor3D v1 = Vetor3D(0,0,0);
    //Vetor3D v2 = Vetor3D(1,0,0);
    //Vetor3D v3 = Vetor3D(0,1,0);

    //exemplo da face frontal da nossa piramide
    Vetor3D vN = Vetor3D(0,1,1);
    Vetor3D v1 = Vetor3D(1,0,1);
    Vetor3D v2 = Vetor3D(0,1,0);
    Vetor3D v3 = Vetor3D(-1,0,1);

    Vetor3D desl = Vetor3D( px,py,0 ); //          R.(T.vi)
    v1 = translacao(v1,desl);
    v2 = translacao(v2,desl);
    v3 = translacao(v3,desl);

    vN = rotacaoZ(vN,theta);
    v1 = rotacaoZ(v1,theta);
    v2 = rotacaoZ(v2,theta);
    v3 = rotacaoZ(v3,theta);

    glBegin(GL_POLYGON);
        glNormal3f( vN.x, vN.y, vN.z );
        glVertex3f( v1.x, v1.y, v1.z );
        glVertex3f( v2.x, v2.y, v2.z );
        glVertex3f( v3.x, v3.y, v3.z );
    glEnd();
}

void piramide2()
{
    //face frontal
    glBegin(GL_POLYGON);
        glNormal3f( 0,1,1 );
        glVertex3f( 1,0,1 );
        glVertex3f( 0,1,0 );
        glVertex3f( -1,0,1 );
    glEnd();

    //face lateral direita
    glPushMatrix();
        glRotatef( 90, 0,1,0 );
        glBegin(GL_POLYGON);
            glNormal3f( 0,1,1 );
            glVertex3f( 1,0,1 );
            glVertex3f( 0,1,0 );
            glVertex3f( -1,0,1 );
        glEnd();
    glPopMatrix();

    //face traseira
    glPushMatrix();
        glRotatef( 180, 0,1,0 );
        glBegin(GL_POLYGON);
            glNormal3f( 0,1,1 );
            glVertex3f( 1,0,1 );
            glVertex3f( 0,1,0 );
            glVertex3f( -1,0,1 );
        glEnd();
    glPopMatrix();

    //face lateral esquerda
    glPushMatrix();
        glRotatef( -90, 0,1,0 );
        glBegin(GL_POLYGON);
            glNormal3f( 0,1,1 );
            glVertex3f( 1,0,1 );
            glVertex3f( 0,1,0 );
            glVertex3f( -1,0,1 );
        glEnd();
    glPopMatrix();
}

void personagem() {
    glPushMatrix(); //pelvis
        glTranslatef(px,py,0);
        glRotatef(thetaPelvis, 0,0,1);

        GUI::drawBox(-0.2,-0.1,-0.1, 0.2,0.1,0.1);

        glPushMatrix(); //tronco
            glTranslatef(0,0.1,0);    //T.R.vi
            glRotatef(thetaTronco, 0,0,1);
            GUI::drawBox(-0.15,0.0,-0.1, 0.15,0.4,0.1);

            glPushMatrix(); //braco esquerdo
                GUI::setColor(1,0,0);
                glTranslatef(0.15,0.4,0);    //T.R.vi
                glRotatef(thetaBracoEsq, 0,0,1);
                GUI::drawBox(-0.05,-0.5,-0.1, 0.05,0.0,0.1);
            glPopMatrix();
            glPushMatrix(); //braco direito
                GUI::setColor(1,0,0);
                glTranslatef(-0.15,0.4,0);    //T.R.vi
                glRotatef(thetaBracoDir, 0,0,1);
                GUI::drawBox(-0.05,-0.5,-0.1, 0.05,0.0,0.1);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

float discrWidth = 0.03;
float discrHeight = 0.03;

void desenha() {
    GUI::displayInit();

    GUI::setLight(0, 1,2,3, true, false);

    //GUI::setColor(1,0.6,0);
    //glDisable(GL_CULL_FACE);
    //GUI::drawFloor();
    //GUI::drawOrigin(0.5);

    GUI::setColor(1,0.6,0,1,true);
    glDisable(GL_CULL_FACE);
    GUI::drawGaussianFloor(px,pz,py-raio*2,raio,5,5,discrWidth,discrHeight);
    glEnable(GL_CULL_FACE);

    GUI::setColor(0,0,1,1,true);
    //piramide();

    //transformacoesSemMatriz();

    //usando as transformacoes do OpenGL (usando matrizes)
    //glTranslatef(px,py,0);   //          T.(R.vi)
    //glRotatef(theta, 0,0,1); //novas matrizes sao multiplicadas à direita da matriz de transformacao atual

    //glBegin(GL_POLYGON);
    //    glNormal3f( 0,1,1 );
    //    glVertex3f( 1,0,1 );
    //    glVertex3f( 0,1,0 );
    //    glVertex3f( -1,0,1 );
    //glEnd();

    //piramide2();

    //piramide();

    //personagem();

    GUI::setColor(1,0,0, 1,true);
    GUI::drawSphere(px,py,pz, raio);
    // //px += 0.001;

    px += 2.0*glutGUI::dtx;
    py += 2.0*glutGUI::dty;
    pz += 2.0*glutGUI::dtz;
    raio += 0.01*glutGUI::dax;
    //theta += glutGUI::daz;

    thetaTronco += glutGUI::dlx;
    thetaPelvis += glutGUI::dly;
    thetaBracoEsq += glutGUI::dlrx;
    thetaBracoDir += 10*glutGUI::dlry;

    GUI::displayEnd();
}

void teclado(unsigned char tecla, int mx, int my) {
    GUI::keyInit(tecla, mx,my);

    switch (tecla) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'a':
        px -= 0.1;
        break;
    case 'd':
        px += 0.1;
        //raio += 0.01;
        break;
    case 's':
        py -= 0.1;
        break;
    case 'w':
        py += 0.1;
        break;

    case '=':
        discrWidth *= 2;
        discrHeight *= 2;
        break;
    case '-':
        discrWidth /= 2;
        discrHeight /= 2;
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

//inicializando OpenGL
//while(true) {
//    desenha();
//    interacaoUsuario();
//    //if () {
//    //    break;
//    //}
//}





















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
