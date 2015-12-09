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

	std::string json_obj = "{\"mFloat\":3.1415926535897932384626433832795,\"mInt\":362880,\"mCad\":\"This, \\\" is a 'test\",\"isObject\":true,\"caracter\":\"$\"}";

    std::string json_arr = "[45.254, 487.000025255, 0.658]";
    
    try
    {
		//DOM style parse json object
        jsonpack::object_t obj;

        obj.json_unpack(json_obj.c_str(), json_obj.length() );
		
        // Explicit type conversion: two ways

//        obj["mFloat"](out.mFloat);
        out.mFloat = obj["mFloat"].get<float>();

//        obj["mInt"](out.mInt);
        out.mInt = obj["mInt"].get<int>();

//        document_obj["mCad"](out.mCad);
        out.mCad = obj["mCad"].get<std::string>();

//        obj["isObject"](out.isObject);
        out.isObject = obj["isObject"].get<bool>();

//        obj["caracter"](out.caracter);
        out.caracter = obj["caracter"].get<char>();

		printf("\nresult: \nout.mFloat=%0.16f\nout.mInt=%d\nout.mCad=%s\nout.isObject=%d\nout.caracter=%c\n",
              out.mFloat, out.mInt, out.mCad.data(), out.isObject, out.caracter );

		//DOM style parse json array
        jsonpack::array_t list;

        list.json_unpack(json_arr.c_str(), json_arr.length() );

        //can be: array, deque, list, forward_list, set, multiset, unordered_set and unordered_multiset.
//        std::vector<double> real_list;
//        list(real_list);
        auto real_list = list.get<std::vector<double>>();

        for(auto v : real_list)
            printf("%f ", v);

		printf("\n");
		
    }
    catch (jsonpack::jsonpack_error &e)
    {
        printf("error: %s\n", e.what());
    }

    getchar();

    return 0;
}
