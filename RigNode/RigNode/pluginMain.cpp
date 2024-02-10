#include "pluginMain.h"



MObject DepNode::angle = MObject();

MStatus DepNode::compute() {
	MGlobal::displayInfo("Hello i am a node");
	return MS::kSuccess;
};


const char* DepNode::name = "DepNode";
MTypeId DepNode::id = MTypeId(0x010085);

void* DepNode::creator()
{
	return new DepNode();
};

MStatus DepNode::initialize()
{
	MFnNumericAttribute numAttr;
	angle = numAttr.create("angle", "fa", MFnNumericData::kFloat, 12.0);

	MGlobal::displayInfo("hew im initialize");

	numAttr.setReadable(1);
	numAttr.setWritable(1);
	numAttr.setStorable(1);
	numAttr.setHidden(0);

	addAttribute(angle);

	return MS::kSuccess;
};


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
