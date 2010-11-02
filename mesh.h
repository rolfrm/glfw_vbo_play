#include <iostream>
class Vert {
public:
	float x, y, z;
	/*void set(float nx, float ny, float nz) {
	 x = nx;
	 y = ny;
	 z = nz;
	 }*/
	 void print(){
		std::cout << x << " " << y << " " << z << "\n";	 
	 }
};

Vert CreateVertex(float x, float y, float z) {
	Vert ret;
	ret.x = x;
	ret.y = y;
	ret.z = z;	
	return ret;
}


typedef Vert Vec;

class TexCoord {
public:
	float u, v;
	void set(float nu, float nv) {
		u = nu;
		v = nv;
	}
};

TexCoord CreateTexCoord(float x, float y){
	TexCoord out;
	out.v = x;
	out.u = y;
	return out;	
}

class Mesh {
/*Vertex mesh class.*/
public:
	int VertexCount;
	Vert * Vertices;
	Vert * Normals;
	TexCoord * TexCoords;
	unsigned int TextureID;
	unsigned int nVBOVertexes;
	unsigned int VBONormals;
	unsigned int nVBOTexCoords;
	
	Vert calc_normal(Vert a, Vert b,Vert c){
		b = CreateVertex(c.x - a.x, c.y - a.y, c.z-a.z);
		a = CreateVertex(c.x-b.x,c.y-b.y,c.z-b.z);
		return CreateVertex(a.y*b.z -a.z*b.x , a.z*b.x - a.x*b.z , a.x*b.y - a.y*b.x);
	}
	
	
	Mesh() {
		VertexCount = 24;
		Vertices = new Vert[VertexCount];
		Vertices[0] = CreateVertex(0, 0, 0);
		Vertices[1] = CreateVertex(0, 1, 0);
		Vertices[2] = CreateVertex(1, 1, 0);
		Vertices[3] = CreateVertex(1, 0, 0);		
		
		Vertices[4] = CreateVertex(0, 0, 1);
		Vertices[5] = CreateVertex(0, 1, 1);
		Vertices[6] = CreateVertex(0, 1, 0);
		Vertices[7] = CreateVertex(0, 0, 0);
		
		Vertices[8] = CreateVertex(0, 1, 1);
		Vertices[9] = CreateVertex(1, 1, 1);
		Vertices[10] = CreateVertex(1, 1, 0);
		Vertices[11] = CreateVertex(0, 1, 0);
		
		Vertices[12] = CreateVertex(0, 0, 1);
		Vertices[13] = CreateVertex(0, 1, 1);
		Vertices[14] = CreateVertex(1, 1, 1);
		Vertices[15] = CreateVertex(1, 0, 1);
		
		Vertices[16] = CreateVertex(0, 0, 1);
		Vertices[17] = CreateVertex(1, 0, 1);
		Vertices[18] = CreateVertex(1, 0, 0);
		Vertices[19] = CreateVertex(0, 0, 0);
		
		Vertices[20] = CreateVertex(1, 0, 1);
		Vertices[21] = CreateVertex(1, 1, 1);
		Vertices[22] = CreateVertex(1, 1, 0);
		Vertices[23] = CreateVertex(1, 0, 0);

		TexCoords = new TexCoord[VertexCount];
		TexCoords[0] = CreateTexCoord(1,0);
		TexCoords[1] = CreateTexCoord(0,1);
		TexCoords[2] = CreateTexCoord(1,1);
		TexCoords[3] = CreateTexCoord(0,1);	
		TexCoords[4] = CreateTexCoord(1,0);
		TexCoords[5] = CreateTexCoord(0,1);

		Normals =new Vert[VertexCount];
		
		Normals[0] = CreateVertex(0,0,1);
		Normals[1] = CreateVertex(0,0,1);
		Normals[2] = CreateVertex(0,0,1);
		Normals[3] = CreateVertex(0,0,1);
		
		Normals[4] = CreateVertex(1,0,0);
		Normals[5] = CreateVertex(1,0,0);
		Normals[6] = CreateVertex(1,0,0);
		Normals[7] = CreateVertex(1,0,0);
		
		Normals[8] = CreateVertex(0,1,0);
		Normals[9] = CreateVertex(0,1,0);
		Normals[10] = CreateVertex(0,1,0);
		Normals[11] = CreateVertex(0,1,0);
		
		Normals[12] = CreateVertex(0,0,-1);
		Normals[13] = CreateVertex(0,0,-1);
		Normals[14] = CreateVertex(0,0,-1);
		Normals[15] = CreateVertex(0,0,-1);
		
		Normals[16] = CreateVertex(0,1,0);
		Normals[17] = CreateVertex(0,1,0);
		Normals[18] = CreateVertex(0,1,0);
		Normals[19] = CreateVertex(0,1,0);
		
		Normals[20] = CreateVertex(1,0,0);
		Normals[21] = CreateVertex(1,0,0);
		Normals[22] = CreateVertex(1,0,0);
		Normals[23] = CreateVertex(1,0,0);
		//Normals[8] = CreateVertex(1,0,0);
		/*Normals[0] = calc_normal(Vertices[0],Vertices[1],Vertices[2]);
		Normals[0].print();
		Normals[1] = calc_normal(Vertices[1],Vertices[2],Vertices[3]);
		Normals[1].print();
		Normals[2] = calc_normal(Vertices[2],Vertices[3],Vertices[4]);
		Normals[2].print();
		Normals[3] = calc_normal(Vertices[3],Vertices[4],Vertices[5]);
		Normals[3].print();*/
	}
	
	
	void BuildVBOs() {
		glGenBuffersARB(1, &nVBOVertexes);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, nVBOVertexes);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, VertexCount * 3 * sizeof(float),
				Vertices, GL_DYNAMIC_DRAW_ARB);

		glGenBuffersARB(1, &nVBOTexCoords);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, nVBOTexCoords);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, VertexCount * 2 * sizeof(float),
				TexCoords, GL_STATIC_DRAW_ARB);


		glGenBuffersARB(1, &VBONormals);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBONormals);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, VertexCount * 3 * sizeof(float),Normals, GL_STATIC_DRAW_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);

		delete Vertices;
		delete TexCoords;
		delete Normals;
	}
};

