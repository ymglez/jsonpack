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
};

int main()
{
    DataObject out;
	std::vector<double> real_list; 
	
	std::string json_obj = "{\"mFloat\":3.1415926535897932384626433832795,\"mInt\":362880,\"mCad\":\"This, \\\" is a 'test\",\"isObject\":true,\"caracter\":\"$\"}";

	std::string json_arr = "[45.254, 487.000025255, 0000.658]";
    
    try
    {
		//DOM style parse json object
		jsonpack::object_t document_obj;

		document_obj.json_unpack(json_obj.c_str(), json_obj.length() );
		
		document_obj["mFloat"](out.mFloat);
		document_obj["mInt"](out.mInt);
		document_obj["mCad"](out.mCad);
		document_obj["isObject"](out.isObject);
		document_obj["caracter"](out.caracter);
		
		printf("\nresult: \nout.mFloat=%0.16f\nout.mInt=%d\nout.mCad=%s\nout.isObject=%d\nout.caracter=%c\n",
              out.mFloat, out.mInt, out.mCad.data(), out.isObject, out.caracter );
		
		jsonpack::clear(&document_obj);

		//DOM style parse json array
		jsonpack::array_t document_list;
		float result = 0;

		document_list.json_unpack(json_arr.c_str(), json_arr.length() );
		for(auto item : document_list)
		{
			item(result);
			real_list.push_back(result);
			printf(" %f", result);
		}
		printf("\n");
		jsonpack::clear(&document_list);
		
    }
    catch (jsonpack::jsonpack_error &e)
    {
        printf("error: %s\n", e.what());
    }

    getchar();

    return 0;
}