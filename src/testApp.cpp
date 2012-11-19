





#include "testApp.h"
#include "RigidMeshDeformer2D.h"


ofMesh m_mesh;
float m_bounds[6];
Wml::Vector2f m_vTranslate;
float m_fScale;
ofMesh m_deformedMesh;
rmsmesh::RigidMeshDeformer2D m_deformer;
bool m_bConstraintsValid;
std::set<unsigned int> m_vSelected;
unsigned int m_nSelected;


void InitializeDeformedMesh();
void UpdateDeformedMesh();
void InvalidateConstraints();
void ValidateConstraints();
unsigned int FindHitVertex( float nX, float nY );




void MakeSquareMesh(){
	m_mesh.clear();
    
    m_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    m_deformedMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    
    float xAdd = 500;
    float yAdd = 500;

	const unsigned int nRowLen = 7;
	
	
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            m_mesh.addVertex(ofPoint(500 + i * 50, 500 + j * 50));
        }
    }

	for ( unsigned int yi = 0; yi < 5-1; ++yi ) {
        unsigned int nRow1 = yi * 5;
		unsigned int nRow2 = (yi+1) * 5;
		for ( unsigned int xi = 0; xi < 5-1; ++xi ) {
			
            
            m_mesh.addIndex(nRow1 + xi);
            m_mesh.addIndex(nRow2 + xi + 1);
            m_mesh.addIndex(nRow1 + xi + 1);
            
            m_mesh.addIndex(nRow1 + xi);
            m_mesh.addIndex(nRow2 + xi);
            m_mesh.addIndex(nRow2 + xi + 1);
            
		}
	}
	
	InitializeDeformedMesh();
	//glutPostRedisplay();
}


//void UpdateScale() 
//{
//	glGetIntegerv(GL_VIEWPORT, m_nViewport);
//	float fViewCenterX = (float)m_nViewport[2] / 2;
//	float fViewCenterY = (float)m_nViewport[3] / 2;
//	
//	m_mesh.GetBoundingBox( m_bounds );
//	m_vTranslate.X() = fViewCenterX  -  0.5f * ( m_bounds[0] + m_bounds[1] );
//	m_vTranslate.Y() = fViewCenterY  -  0.5f * ( m_bounds[2] + m_bounds[3] );
//	
//	float fWidth = m_bounds[1] - m_bounds[0];
//	float fHeight = m_bounds[3] - m_bounds[2];
//	float fSizeObject = std::max(fWidth,fHeight);
//	float fSizeView = std::min( m_nViewport[2], m_nViewport[3] );
//	
//	m_fScale = 0.5f * (fSizeView / fSizeObject);
//}
//Wml::Vector2f ViewToWorld(  Wml::Vector2f  vPoint )
//{
//	//return (vPoint - m_vTranslate) / m_fScale;
//	
//	Wml::Vector2f ret;
//	ret.X() = (vPoint.X()-m_vTranslate.X()) / m_fScale;
//	ret.Y() = (vPoint.Y()-m_vTranslate.Y()) / m_fScale;
//	
//	//cout << vPoint.X() << endl;
//	return ret;
//	
//	
//}
//Wml::Vector2f WorldToView(  Wml::Vector2f  vPoint )
//{
//	
//	Wml::Vector2f ret;
//	ret.X() = vPoint.X() * m_fScale  + m_vTranslate.X();
//	ret.Y() = vPoint.Y() * m_fScale  + m_vTranslate.Y();
//	
//	//cout << vPoint.X() << endl;
//	return ret; //( vPoint * m_fScale ) + m_vTranslate;
//}




void InitializeDeformedMesh()
{
	m_deformedMesh.clear();
	
	unsigned int nVerts = m_mesh.getVertices().size();
	
	for ( unsigned int i = 0; i < nVerts; ++i ) {
		ofVec2f vVertex(0,0);
        vVertex = m_mesh.getVertices()[i];
        m_deformedMesh.addVertex(vVertex);
		//m_mesh.GetVertex(i, vVertex);
		//m_deformedMesh.AppendVertex(vVertex);
	}
    
    for ( unsigned int i = 0; i < m_mesh.getIndices().size(); ++i ) {
		int index = m_mesh.getIndices()[i];
        m_deformedMesh.addIndex(index);
		//m_mesh.GetVertex(i, vVertex);
		//m_deformedMesh.AppendVertex(vVertex);
	}
    
    
	
//    // TODO this is problematic
//	unsigned int nTris = m_mesh.GetNumTriangles();
//	for ( unsigned int i = 0; i < nTris; ++i ) {
//		unsigned int nTriangle[3];
//		m_mesh.GetTriangle(i,nTriangle);
//		m_deformedMesh.AppendTriangleData(nTriangle);
//	}
	
	m_deformer.InitializeFromMesh( &m_mesh );
	InvalidateConstraints();
	
//	vector < ofVec2f > vert = m_mesh.getVertices();
//	//vector <unsigned int > tris = m_mesh.GetTriangles();
//	
//	vert = m_deformedMesh.getVertices();
//	//tris = m_deformedMesh.GetTriangles();
//	
//	//cout << " --------- deform ------------ " << endl;
//    //	for (int i = 0; i < vert.size(); i++){
//    //		cout << vert[i] << ",";	
//    //	}
//    //	cout << endl;
//    //	
//    //	for (int i = 0; i < tris.size(); i++){
//    //		cout << tris[i] << ",";	
//    //	}
//    //	cout << endl;
	
	
}



void UpdateDeformedMesh() 
{
	ValidateConstraints();
	m_deformer.UpdateDeformedMesh( &m_deformedMesh, true );
	
	//vector < ofVec3f > vert = m_mesh.getVertices();
    //vector <unsigned int > tris = m_mesh.GetTriangles();
	
	//cout << " --------- orig ------------ " << endl;
    //	for (int i = 0; i < vert.size(); i++){
    //		cout << vert[i] << ",";	
    //	}
    //	cout << endl;
    //	
    //	for (int i = 0; i < tris.size(); i++){
    //		cout << tris[i] << ",";	
    //	}
    //	cout << endl;
	
	
	
    vector < ofVec3f > vert = m_deformedMesh.getVertices();
    //tris = m_deformedMesh.GetTriangles();

        cout << " --------- deform ------------ " << endl;
        for (int i = 0; i < vert.size(); i++){
            cout << vert[i] << ",";	
        }
        cout << endl;
    //	
    //	for (int i = 0; i < tris.size(); i++){
    //		cout << tris[i] << ",";	
    //	}
    //	cout << endl;
	
	
}


// deformer stuff
void InvalidateConstraints() 
{ 
	m_bConstraintsValid = false; 
}

void ValidateConstraints()
{
	if ( m_bConstraintsValid )
		return;
	
	size_t nConstraints = m_vSelected.size();
	std::set<unsigned int>::iterator cur(m_vSelected.begin()), end(m_vSelected.end());
	while ( cur != end ) {
		unsigned int nVertex = *cur++;
		ofVec3f vVertex;
        
        ///cout << " validate " << nVertex << endl;
        
		vVertex = m_deformedMesh.getVertices()[nVertex]; //( nVertex, vVertex);
		m_deformer.SetDeformedHandle( nVertex, ofVec2f( vVertex.x, vVertex.y ) );
	}
	
	m_deformer.ForceValidation();
	
	m_bConstraintsValid = true;
}


// selection stuff

unsigned int FindHitVertex( float nX, float nY ){
	
	
	vector < ofVec3f > verts = m_deformedMesh.getVertices();
	
	unsigned int nVerts = m_deformedMesh.getVertices().size();
	for ( unsigned int i = 0; i < nVerts; ++i ) {
		
		ofVec3f vVertex;
		//m_deformedMesh.GetVertex(i, vVertex);
		vVertex = verts[i];
		
		ofVec2f temp = ofVec2f(vVertex.x, vVertex.y);
		
		ofVec2f vView = temp;; //WorldToView( temp );
		//cout << vView.X() << endl;
		
		float fX = vView.x;
		float fY = vView.y;
		
		//
		
		double fDist = sqrt( 
							(double)((nX - fX)*(nX - fX) + (nY-fY)*(nY-fY) ));
		if ( fDist < 5 ) 
			return i;
	}
	
	return std::numeric_limits<unsigned int>::max();
}



//--------------------------------------------------------------
void testApp::setup(){
MakeSquareMesh();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    UpdateDeformedMesh();

    
    glLineWidth(2.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	
    //ofRect(mouseX, mouseY,2,2);
    
    m_deformedMesh.drawWireframe();
	
//	vector < unsigned int > tris = m_deformedMesh.GetTriangles();
//	vector < float > verts = m_deformedMesh.GetVertices();
//	
//	unsigned int nTris = m_deformedMesh.GetNumTriangles();
//	for ( unsigned int i = 0; i < nTris; ++i ) {
//		Wml::Vector3f vVerts[3];
//		
//		vVerts[0][0] = verts[ tris[(i * 3)]*4 ];
//		vVerts[0][1] = verts[ tris[(i * 3)]*4 +1];
//		vVerts[1][0] = verts[ tris[(i * 3+1)]*4 ];
//		vVerts[1][1] = verts[ tris[(i * 3+1)]*4 +1];
//		vVerts[2][0] = verts[ tris[(i * 3+2)]*4 ];
//		vVerts[2][1] = verts[ tris[(i * 3+2)]*4 +1];
//		
//		glBegin(GL_LINE_LOOP);
//		glVertex2fv( vVerts[0] );
//		glVertex2fv( vVerts[1] );
//		glVertex2fv( vVerts[2] );
//        
//		glEnd();
//	}
	
	//glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();
    
	std::set<unsigned int>::iterator cur(m_vSelected.begin()), end(m_vSelected.end());
	while ( cur != end ) {
		unsigned int nSelected = *cur++;
		
		ofVec3f vSelected;
		vSelected = m_deformedMesh.getVertices()[nSelected];  //( nSelected, vSelected );
		ofVec2f vView = ofVec2f(vSelected.x,vSelected.y);
		
		glBegin(GL_QUADS);
		glVertex2f( vView.x - 5, vView.y - 5 );
		glVertex2f( vView.x + 5, vView.y - 5 );
		glVertex2f( vView.x + 5, vView.y + 5 );
		glVertex2f( vView.x - 5, vView.y + 5 );
		glEnd();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    if ( m_nSelected != std::numeric_limits<unsigned int>::max() ) {
		//Wml::Vector3f vNewPosView( (float)x, (float)(y), 0.0 );
		//Wml::Vector2f vNewPosWorld = ViewToWorld( vNewPosView );
		//Wml::Vector3f vNewPos( vNewPosWorld.X(), vNewPosWorld.y, 0.0f );
		m_deformedMesh.getVertices()[m_nSelected].set(x,y); //                 //SetVertex( m_nSelected, vNewPosView );
		InvalidateConstraints();
		//glutPostRedisplay();
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    
    
        if ( button == 0 ) {
             m_nSelected = FindHitVertex( (float)x, (float)(y) );
            //cout << m_nSelected << endl;
        }
    
    
    if ( button == 2) {
        unsigned int nHit = FindHitVertex( (float)x, (float)(y) );
        if ( nHit != std::numeric_limits<unsigned int>::max() ) {
            if ( m_vSelected.find(nHit) == m_vSelected.end() )
                m_vSelected.insert(nHit);
            else {
                m_vSelected.erase(nHit);
                m_deformer.RemoveHandle(nHit);
                
                // restore position
                ofVec3f vVertex;
                vVertex = m_mesh.getVertices()[nHit];
                m_deformedMesh.getVertices()[nHit] = vVertex; //(nHit, vVertex);
            }
            InvalidateConstraints();
            //glutPostRedisplay();
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    if ( button == 0 ) {
        m_nSelected = std::numeric_limits<unsigned int>::max();
    } 

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
















//void OnMouseClick(int button, int state, int x, int y) 
//{
//	
//	
//	if ( button == GLUT_LEFT_BUTTON ) {
//		
//		if ( state == GLUT_DOWN )
//			m_nSelected = FindHitVertex( (float)x, (float)(m_nViewport[3] - 1 - y) );
//		else
//			m_nSelected = std::numeric_limits<unsigned int>::max();
//		glutPostRedisplay();
//		
//	} else if ( button == GLUT_RIGHT_BUTTON && state == GLUT_UP ) {
//		
//		unsigned int nHit = FindHitVertex( (float)x, (float)(m_nViewport[3] - 1 - y) );
//		if ( nHit != std::numeric_limits<unsigned int>::max() ) {
//			
//			if ( m_vSelected.find(nHit) == m_vSelected.end() )
//				m_vSelected.insert(nHit);
//			else {
//				m_vSelected.erase(nHit);
//				m_deformer.RemoveHandle(nHit);
//				
//				// restore position
//				Wml::Vector3f vVertex;
//				m_mesh.GetVertex(nHit,vVertex);
//				m_deformedMesh.SetVertex(nHit, vVertex);
//			}
//			
//			InvalidateConstraints();
//			//glutPostRedisplay();
//		}
//		
//	}
//	
//}



//void OnKeyboard(unsigned char key, int x, int y)
//{
//	if ( key == 'f' ) {
//		/*CFileDialog openDlg(TRUE, "obj", "mesh.obj", 0, "OBJ Files (*.obj)|*.obj|");
//         if ( openDlg.DoModal() == IDOK ) {
//         
//         m_mesh.Clear();
//         m_mesh.read( (LPCTSTR)openDlg.GetPathName() );
//         m_vSelected.clear();
//         InitializeDeformedMesh();
//         
//         glutPostRedisplay();
//         }*/
//	}
//}








	//
	



