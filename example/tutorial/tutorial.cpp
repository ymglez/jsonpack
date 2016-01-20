#include <jsonpack.hpp>

struct  DataObject
{
	DataObject():
        mInt(362880),
        mFloat(3.1415926535897932384626433832795f),
        mCad("This, \" is a \", \'test"),
		isObject(true),
        caracter('$'),
        degrees({{"Washington", {12.5, 15.2}},{"Havana", {25.3, 23.4}},{"Singapour", {6.0}}})
	{}

	int mInt;
	float mFloat;
	std::string mCad;
	bool isObject;
	char caracter;
    std::map<std::string, std::vector<float>> degrees ;

	// The defined members, will be the JSON attributes set
	// Pairs <"key" : value>, are: <"member-name" : member-value >
    DEFINE_JSON_ATTRIBUTES(mFloat, mInt, mCad, isObject, caracter, degrees)
};

int main()
{
	// manage my object
    DataObject src, out;

	//serialize object
    //pretty print
    //param bool pretty     if or not output will be pretty-printed
    //param unsigned indent degree of indentation(spaces)
    char* serialized = src.json_pack(true, 2);
    printf("pretty json: \n%s\n", serialized);
	
	//deserialize json
	try
	{
		out.json_unpack(serialized, strlen(serialized) );
        printf("\ndeserialized object:\n %s\n", out.json_pack());
    }
	catch (jsonpack::jsonpack_error &e)
	{
		printf("error: %s\n", e.what());
	}

	free(serialized);
	getchar();
	return 0;
}
