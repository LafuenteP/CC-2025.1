gui.cpp

    float GUI::gauss(float x, float z, float centroX, float centroZ, float amplitude, float larg) {
        return amplitude*pow(M_E,-pow(x-centroX,2)/(2*pow(larg,2))-pow(z-centroZ,2)/(2*pow(larg,2)));
    }

    void GUI::drawGaussianFloor(float centroX, float centroZ, float amplitude, float larg, float width, float height, float discrWidth, float discrHeight, float texWidth, float texHeight, bool inverted)
    {
        float discrTexWidth = texWidth/width;
        float discrTexHeight = texHeight/height;
        for(float i=-0.5*width;i<0.5*width;i+=discrWidth) {
            for(float j=-0.5*height;j<0.5*height;j+=discrHeight) {
                glPushMatrix();
                    if (inverted) glRotatef(180,1,0,0);
                    glTranslatef(i,0.0,j);
                    glBegin( GL_QUADS );
                        glNormal3f(0.,1.,0.);
                            glTexCoord2f(     i*discrTexWidth, (j+1)*discrTexHeight); glVertex3f(        0.0,gauss(           i,j+discrHeight,centroX,centroZ,amplitude,larg),+discrHeight);
                            glTexCoord2f( (i+1)*discrTexWidth, (j+1)*discrTexHeight); glVertex3f(+discrWidth,gauss(i+discrWidth,j+discrHeight,centroX,centroZ,amplitude,larg),+discrHeight);
                            glTexCoord2f( (i+1)*discrTexWidth,     j*discrTexHeight); glVertex3f(+discrWidth,gauss(i+discrWidth,            j,centroX,centroZ,amplitude,larg),         0.0);
                            glTexCoord2f(     i*discrTexWidth,     j*discrTexHeight); glVertex3f(        0.0,gauss(           i,            j,centroX,centroZ,amplitude,larg),         0.0);
                    glEnd();
                glPopMatrix();
            }
        }
    }



main.cpp

    //GUI::setColor(1,0.6,0);
    //glDisable(GL_CULL_FACE);
    //GUI::drawFloor();
    //GUI::drawOrigin(0.5);

    GUI::setColor(1,0.6,0);
    glDisable(GL_CULL_FACE);
    GUI::drawGaussianFloor(px,pz,py-raio*2,raio,5,5,0.03,0.03);
    glEnable(GL_CULL_FACE);

    //personagem();

    GUI::setColor(1,0,0, 1,true);
    GUI::drawSphere(px,py,pz, raio);
    // //px += 0.001;

    px += 0.5*glutGUI::dtx;
    py += 0.5*glutGUI::dty;
    pz += 0.5*glutGUI::dtz;
    raio += 0.01*glutGUI::dax;
    //theta += glutGUI::daz;

