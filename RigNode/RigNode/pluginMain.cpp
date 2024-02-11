#include "pluginMain.h"



MObject DepNode::parentMatrix = MObject();

MStatus DepNode::compute() {
	MGlobal::displayInfo("Hello i am a node");
	return MS::kSuccess;
};


const char* DepNode::name = "DepNode";
MTypeId DepNode::id = MTypeId(0x010085);

void* DepNode::creator()
{
	return new DepNode();
}

MStatus DepNode::initialize()
{
	MGlobal::displayInfo("Call to initialize node. making pointer");
	MFnMatrixAttribute matrixAttribute;


	MGlobal::displayInfo("Matrix attr pointer made calling to create attributes");


	MObject parentMatrixAttr = matrixAttribute.create("ParentMatrix", "pm", MFnMatrixAttribute::kFloat);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(0);
	matrixAttribute.setStorable(1);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(parentMatrixAttr);


	MObject childMatrixAttr = matrixAttribute.create("ChildMatrix", "cm", MFnMatrixAttribute::kFloat);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(0);
	matrixAttribute.setStorable(1);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(childMatrixAttr);


	MObject resultMatrixAttr = matrixAttribute.create("ResultMatrix", "rm", MFnMatrixAttribute::kFloat);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(1);
	matrixAttribute.setStorable(0);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(resultMatrixAttr);

	MGlobal::displayInfo("All attributes made");

	attributeAffects(parentMatrixAttr, resultMatrixAttr);
	attributeAffects(childMatrixAttr, resultMatrixAttr);

	MGlobal::displayInfo("Attr pointer released");

	return MS::kSuccess;
};

//MObject DepNode::initializeMatrixAttr(MFnMatrixAttribute matrixAttribute, MString fullName, MString briefName, MFnMatrixAttribute::Type matrixType, bool isWritable, bool isReadable)
//{
//
//	MGlobal::displayInfo("Creating attribute");
//	MObject newAttribute = matrixAttribute.create(fullName, briefName, MFnMatrixAttribute::kFloat);
//	MObject newAttribute = MObject();
//
//	/*matrixAttribute->setWritable(isWritable);
//	matrixAttribute->setReadable(isReadable);
//
//	matrixAttribute->setStorable(1);
//	matrixAttribute->setConnectable(1);
//	matrixAttribute->setChannelBox(1);
//	matrixAttribute->setHidden(0);*/
//
//	return newAttribute;
//};


// Plugin initializers \\

MStatus initializePlugin(MObject obj)
{
	const char* pluginVendor = "Tanner";
	const char* pluginVersion = "0.0.01";

	MFnPlugin plugin(obj, pluginVendor, pluginVersion);

	const char* initializeMessage = "Plug has been initialized! Creating a node";

	MGlobal::displayInfo(initializeMessage);

	plugin.registerNode(DepNode::name, DepNode::id, DepNode::creator, DepNode::initialize);


	return (MS::kSuccess);
}

MStatus uninitializePlugin(MObject obj)
{

	MFnPlugin plugin(obj);
	plugin.deregisterNode(DepNode::id);

	const char* uninitializeMessage = "Plugin is now uninitialized :(";
	MGlobal::displayWarning(uninitializeMessage);


	return (MS::kSuccess);
}
