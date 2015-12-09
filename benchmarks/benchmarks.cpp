#define JSONPACK_BENCHMARK_MAIN

#include <fstream>
#include <benchpress.hpp>
#include <jsonpack.hpp>

BENCHMARK("parse jeopardy.json", [](benchpress::context* ctx)
{
	std::ifstream inputs_json("files/jeopardy/jeopardy.json");
    std::string* json = new std::string( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));
	
	//expensive setup before before run
	ctx->reset_timer();

    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
        jsonpack::array_t j;
        j.json_unpack(json->c_str(), json->length() );
    }
})

BENCHMARK("parse canada.json", [](benchpress::context* ctx)
{
	std::ifstream inputs_json("files/nativejson-benchmark/canada.json");
    std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));
	
	ctx->reset_timer();

    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
        jsonpack::object_t j;
		j.json_unpack(json.c_str(), json.length() );
    }
})

BENCHMARK("parse citm_catalog.json", [](benchpress::context* ctx)
{
	std::ifstream inputs_json("files/nativejson-benchmark/citm_catalog.json");
    std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));
	
	ctx->reset_timer();

    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
        jsonpack::object_t j;
		j.json_unpack(json.c_str(), json.length() );
    }
})

BENCHMARK("parse twitter.json", [](benchpress::context* ctx)
{
	std::ifstream inputs_json("files/nativejson-benchmark/twitter.json");
    std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));
	
	ctx->reset_timer();

    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
        jsonpack::object_t j;
		j.json_unpack(json.c_str(), json.length() );
    }
})
