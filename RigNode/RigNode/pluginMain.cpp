#include "pluginMain.h"




MStatus DepNode::compute(const MPlug & plug, MDataBlock & dataBlock) {
	//MObject current = plug.asMObject();

	/*if (plug == parentMatrix)
	{
		MGlobal::displayInfo("computecalled");
		MGlobal::displayInfo("current plug is for parent");
		MDataHandle parentMatrix = block.inputValue(DepNode::parentMatrix);
		MGlobal::displayInfo("Got data handle for plug");
		MMatrix matrix = parentMatrix.asMatrix();
	};*/

	if (typeid(plug).name() == typeid(parentMatrix).name())
	{
		cout << "plug type is an object";
		MGlobal::displayInfo("..plug type is an object");
	}
	MGlobal::displayInfo("Got data handle for plug");
	cout << "test";

	MDataHandle parentMatrixHandle = dataBlock.inputValue(parentMatrix);
	MGlobal::displayInfo("got handle");
	cout << "getting matri";

	MMatrix parentMatrix = parentMatrixHandle.asMatrix();
	MGlobal::displayInfo("got matrix");

	MDataHandle childMatrixHandle = dataBlock.inputValue(childMatrix);
	MMatrix childMatrix = childMatrixHandle.asMatrix();

	MDataHandle resultMatrixHandle = dataBlock.outputValue(resultMatrix);

	MMatrix resultMatrix = parentMatrix;
	resultMatrix.operator*=(childMatrix);

	resultMatrixHandle.setMMatrix(resultMatrix);

	dataBlock.setClean(plug);

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


	MObject parentMatrix = matrixAttribute.create("ParentMatrix", "pm", MFnMatrixAttribute::kDouble);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(0);
	matrixAttribute.setStorable(1);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(parentMatrix);


	MObject childMatrix = matrixAttribute.create("ChildMatrix", "cm", MFnMatrixAttribute::kDouble);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(0);
	matrixAttribute.setStorable(1);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(childMatrix);


	MObject resultMatrix = matrixAttribute.create("ResultMatrix", "rm", MFnMatrixAttribute::kDouble);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(1);
	matrixAttribute.setStorable(0);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(resultMatrix);

	MGlobal::displayInfo("All attributes made");

	attributeAffects(parentMatrix, resultMatrix);
	attributeAffects(childMatrix, resultMatrix);

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
