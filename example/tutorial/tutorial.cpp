#include <jsonpack.hpp>

struct  DataObject
{
	int mInt = 0;
	float mFloat = 0.0;
	std::string mCad = "";
	bool isObject = true;
	char caracter = 0;

	// The defined members, will be the JSON attributes set
	// Pairs <"key" : value>, are: <"member-name" : member-value >
	DEFINE_JSON_ATTRIBUTES(mFloat, mInt, mCad, isObject, caracter)
};

int main()
{

	// manage my object
	DataObject src, out;

	src.mFloat = 3.1415926535897932384626433832795;
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
	  printf("\nobject: \nout.mFloat=%0.16f\nout.mInt=%d\nout.mCad=%s\nout.isObject=%d\nout.caracter=%c\n",
			  out.mFloat, out.mInt, out.mCad.data(), out.isObject, out.caracter
			 );
	}
	catch (jsonpack::jsonpack_error &e)
	{
		printf("error: %s\n", e.what());
	}


	free(serialized);
	getchar();

	return 0;
}
