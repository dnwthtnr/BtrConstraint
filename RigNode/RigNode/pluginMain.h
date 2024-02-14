#pragma once
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnAttribute.h>
#include <maya/MPxNode.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MObject.h>



class DepNode : public MPxNode
{
public:

	static const char* name;
	static MTypeId id;


	using MPxNode::MPxNode;


	MObject parentMatrix;
	MObject childMatrix;
	MObject resultMatrix;

	static void* creator();

	static MStatus initialize();

	MStatus compute(const MPlug& plug, MDataBlock& block);

private:

};