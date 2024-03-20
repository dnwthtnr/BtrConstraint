#include "pluginMain.h"




MStatus DepNode::compute(const MPlug &plug, MDataBlock &dataBlock) {
	//MObject current = plug.asMObject();

	/*if (plug == parentMatrix)
	{
		MGlobal::displayInfo("computecalled");
		MGlobal::displayInfo("current plug is for parent");
		MDataHandle parentMatrix = block.inputValue(DepNode::parentMatrix);
		MGlobal::displayInfo("Got data handle for plug");
		MMatrix matrix = parentMatrix.asMatrix();
	};*/

	/*if (typeid(plug).name() == typeid(parentMatrix).name())
	{
		cout << "plug type is an object";
		MGlobal::displayInfo("..plug type is an object");
	}*/
	MGlobal::displayInfo("Got data handle for plug");
	MGlobal::displayInfo(typeid(plug).name());


	try
	{
	//MGlobal::displayInfo(parentMatrixHandle.type());
	MFloatMatrix &parentMatrix = dataBlock.inputValue(parentMatrixAttr).asFloatMatrix();
	//printMatrix(parentMatrix);

	MGlobal::displayInfo("got handle");

	MFloatMatrix &childMatrix = dataBlock.inputValue(childMatrixAttr).asFloatMatrix();
	//printMatrix(childMatrix);

	MGlobal::displayInfo("got matrix");

	//MFloatMatrix &resultMatrix = parentMatrix;
	MFloatMatrix resultMatrix = parentMatrix + childMatrix; // causing error


	MDataHandle outMatrixHandle = dataBlock.outputValue(resultMatrixAttr);
	MFloatMatrix & outMatrix = outMatrixHandle.asFloatMatrix();

	
	MGlobal::displayInfo("got result matrix");

	outMatrix = resultMatrix;
	
	//resultMatrixHandle.setMFloatMatrix(parentMatrix);

	MGlobal::displayInfo("set result x");
	}
	catch (const std::exception& e)
	{
		MGlobal::displayError(e.what());
		return MS::kFailure;
	};

	MGlobal::displayInfo("Escaped try except");

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


	MObject parentMatrixAttr = matrixAttribute.create("ParentMatrix", "pm", MFnMatrixAttribute::kDouble);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(0);
	matrixAttribute.setStorable(1);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(parentMatrixAttr);


	MObject childMatrixAttr = matrixAttribute.create("ChildMatrix", "cm", MFnMatrixAttribute::kDouble);
	matrixAttribute.setWritable(1);
	matrixAttribute.setReadable(0);
	matrixAttribute.setStorable(1);
	matrixAttribute.setConnectable(1);
	matrixAttribute.setChannelBox(1);
	matrixAttribute.setHidden(0);
	addAttribute(childMatrixAttr);


	MObject resultMatrixAttr = matrixAttribute.create("ResultMatrix", "rm", MFnMatrixAttribute::kDouble);
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


void DepNode::printMatrix(MFloatMatrix& matrix) {

	int row, column;
	for (row=0; row < 4; row++){
		MGlobal::displayInfo("row");
		MGlobal::displayInfo( MString("Row:").operator+=(row) );

		for (column = 0; column < 4; column++) {
			MGlobal::displayInfo("col");

			// This line causes an unauthorized read error 
			//const double value = matrix(row, column);

			MGlobal::displayInfo("got row/col");

			//MGlobal::displayInfo( MString("").operator+=(value) );
		}
	}


}


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
