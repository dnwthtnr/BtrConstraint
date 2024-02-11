#pragma once
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnAttribute.h>
#include <maya/MPxNode.h>
#include <maya/MFnMatrixAttribute.h>



class DepNode : public MPxNode
{
public:

	static const char* name;
	static MTypeId id;


	using MPxNode::MPxNode;


	static MObject parentMatrix;
	static MObject childMatrix;
	static MObject resultMatrix;

	static void* creator();

	static MObject initializeMatrixAttr(
		MFnMatrixAttribute* matrixAttribute,
		MString fullName, 
		MString briefName, 
		MFnMatrixAttribute::Type matrixType,
		bool isWritable=true,
		bool isReadable=false
	);

	static MStatus initialize();

	MStatus compute();

private:

};