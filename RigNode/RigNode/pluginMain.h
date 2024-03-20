#pragma once
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnAttribute.h>
#include <maya/MPxNode.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFloatMatrix.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MObject.h>

#include <string>
#include <format>
#include <stdio.h>
#include <iostream>



class DepNode : public MPxNode
{
public:

	static const char* name;
	static MTypeId id;


	using MPxNode::MPxNode;


	MObject parentMatrixAttr;
	MObject childMatrixAttr;
	MObject resultMatrixAttr;

	static void* creator();

	static MStatus initialize();

	static void printMatrix(MFloatMatrix& matrix);

	MStatus compute(const MPlug& plug, MDataBlock& block);

private:

};