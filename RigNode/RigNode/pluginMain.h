#pragma once
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnAttribute.h>
#include <maya/MPxNode.h>



class DepNode : public MPxNode
{
public:

	static const char* name;
	static MTypeId id;


	using MPxNode::MPxNode;

	static MObject angle;

	static void* creator();
	static MStatus initialize();

	MStatus compute();

private:

};