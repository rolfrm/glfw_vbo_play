#pragma once
#include <list>
#include <stack>
#include <armadillo>
#include "mesh2d.h"
#include "material.h"
#include <string>
#include <map>
using namespace std;

class camera;
class light;
class sceneGraph {
public:
	enum PASSTYPE {
		UPDATE, RENDER, RENDERTEX, RENDERGLOW
	};
	class node {
	public:
		list<node *> children;
		virtual void activate();
		virtual void deactivate();
		virtual void update();
		virtual void render();
		void addChild(node * child);
		void traverse(PASSTYPE pst);
		PASSTYPE pst;
		std::string id;

	};

	class orderedNode: public node {
	public:
		list<node *> orderedChildren;
		enum POSITION {
			FRONT, BACK
		};
		void activate();
		void deactivate();
		void addOrderedChild(node * child, POSITION pos);
	};

	class materialNode: public node {
	public:
		materialNode(material * m);
		void activate();
		void deactivate();
		static material * getTopMaterial();
	private:
		material * mat;
		static stack<material *> materialstack;
	};

	class transformNode: public node {
	public:
		transformNode();
		void activate();
		void deactivate();
		void rotate(float xDegrees, float yDegrees, float zDegrees);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void print();
		void printTotalTranslation();

		static arma::Mat<float> getTotalTranslation();

	private:
		arma::Mat<float> translation;
		static arma::Mat<float> totalTranslation;
		arma::Mat<float> savedTranslationMatrix;

	};

	class cameraLeaf: public node {
	public:
		cameraLeaf();
		void activate();
		void update();
		void setCam(camera * cam);
	private:
		camera * cam;
	};

	class VBOLeaf: public node {
	public:
		VBOLeaf();
		VBOLeaf(mesh * newmeshobject);
		void setMesh(mesh * newmeshobject);
		void activate();
		//void deactivate();
	private:
		mesh * meshObject;
	};

	class lightLeaf: public node {
	public:
		lightLeaf(light * lightData);
		void activate();
		light * lightData;
	};

	lightLeaf * createLightLeaf(light * lightdata, node * parent = NULL);
	VBOLeaf * createVBOLeaf(mesh * vboobject, node * parent = NULL);
	cameraLeaf * createCameraLeaf(camera * cameraObject, node * parent =NULL);
	transformNode * createTransformNode(node*  parent = NULL);
	materialNode * createMaterialNode(material * mat, node * parent = NULL);
	orderedNode * createOrderedNode(node * parent);
	private:
	std::map<bool,std::string> nodeIds;

	std::list<lightLeaf*> lightLeafs;
	std::list<cameraLeaf*> cameraLeafs;
	std::list<VBOLeaf *> VBOLeafs;
	std::list<transformNode *> transformNodes;
	std::list<materialNode *> materialNodes;
	std::list<orderedNode *> orderedNodes;
	std::list<node *> allNodes;
};
