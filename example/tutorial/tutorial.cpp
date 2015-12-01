#include <jsonpack.hpp>

struct  DataObject
{
	DataObject():
		mInt(0),
		mFloat(0.0),
		mCad(""),
		isObject(true),
		caracter(0)
	{}

	int mInt;
	float mFloat;
	std::string mCad;
	bool isObject;
	char caracter;

	// The defined members, will be the JSON attributes set
	// Pairs <"key" : value>, are: <"member-name" : member-value >
	DEFINE_JSON_ATTRIBUTES(mFloat, mInt, mCad, isObject, caracter)
};

int main()
{

	// manage my object
	DataObject src, out;

	src.mFloat = 3.1415926535897932384626433832795f;
	src.mInt = 362880;
	src.mCad = "This, \" is a \", \'test";
	src.isObject = true;
	src.caracter = '$';

	//serialize object
	char* serialized = src.json_pack();
	printf("json: \n%s\n", serialized);

	//deserialize json
	try
	{
		out.json_unpack(serialized, strlen(serialized) );
		printf("\ndeserialized object: \nout.mFloat=%0.16f\nout.mInt=%d\nout.mCad=%s\nout.isObject=%d\nout.caracter=%c\n",
			out.mFloat, out.mInt, out.mCad.data(), out.isObject, out.caracter );
	}
	catch (jsonpack::jsonpack_error &e)
	{
		printf("error: %s\n", e.what());
	}


	free(serialized);

	getchar();

	return 0;
}
