#include <iostream>
#include <string>
#include <map>
#include <pair>

#if defined(ARC16)
	#define WORD_TYPE int_16t
	#define U_WORD_TYPE uint_16t
#elif defined(ARC32)
	#define WORD_TYPE int_32t
	#define U_WORD_TYPE uint_32t
#elif defined(ARC64)
	#define WORD_TYPE int_64t
	#define U_WORD_TYPE uint_64t
#endif


#if defined(_WINDOWS_)
	#include
#elif defined(_UNIX_)
	#include
#elif defined(_MACH_)
	#include
#endif


class color_space;
class pix;
class pixrow;
class pixblock;
class image_stack;
class tool;
class tool_map;
class codec;
class codec_map;
class mangler;
class mang_map;
class map_populator;

typedef std::pair<string, unsigned int> color_space_key_pairing;
typedef void (* tool_function)(std::stringstream *);
typedef void (* mang_function)(pixblock *, std::stringstream *);
typedef pixblock * (* codec_function)(file *, std::stringstream *);

class file
{
public:
	std::fstream file_stream;

	file & operator"" instantiate_from_file_path(std::string file_path);
private:
	std::string file_path;
	std::string file_extension;
};

class color_space
{
	friend class pixblock;
public:
	inline pix & operator=(int new_val);
	inline pix & operator=(long new_val);
	inline pix & operator=(unsigned int new_val);
	inline pix & operator=(unsigned long new_val);

	inline operator int();
	inline operator long();
	inline operator unsigned int();
	inline operator unsigned long();



private:

	color_space();

	std::map<std::string, unsigned long> color_space_key_map;
	
	bool set_from_pixel_ref(pix * from_pixel_ptr);

	unsigned int required_bit_depth;

	std::string current_get_value;

	pix & from_pixel_ref;

};

class pix
{
	friend class color_space;
public:
	inline pix & operator=(int new_val);
	inline pix & operator=(long new_val);
	inline pix & operator=(unsigned int new_val);
	inline pix & operator=(unsigned long new_val);
	//inline pix & operator=(WORD_TYPE new_val);
	//inline pix & operator=(U_WORD_TYPE new_val);
	inline operator int();
	inline operator long();
	inline operator unsigned int();
	inline operator unsigned long();

	inline color_space & operator[](string value_string);
	//inline operator WORD_TYPE();
	//inline operator U_WORD_TYPE();
	//inline unsigned int get_bit_depth();


	//inline bool set_depth(unsigned int new_depth);

	
	
private:
	pix(pixrow * from_row_ptr);

	pixrow & from_row_ref;

	unsigned long * pixel_val;
	unsigned long bit_mask;


};

class pixrow
{
	friend class pixblock;
public:
	inline pixrow & operator=(int*);
	inline pixrow & operator=(long*);
	inline pixrow & operator=(unsigned int*);
	inline pixrow & operator=(unsigned long*);

	inline pix & operator[](unsigned int pixel_index);

	inline operator int*();
	inline operator long*();
	inline operator unsigned int*();
	inline operator unsigned long*();

	inline unsigned int length();


private:
	pixrow(pixblock * from_block_ptr);

	pixblock & from_block_ref;

	pix pixel_access_buffer;

	unsigned long * pixel_row;

};

class pixblock
{
public:
	inline operator int**();
	inline operator long**();
	inline operator unsigned int**();
	inline operator unsigned long**();

	inline operator=(int**);
	inline operator=(long**);
	inline operator=(unsigned int**);
	inline operator=(unsigned long**);

	inline pixrow & operator[](unsigned int row_index);

	inline unsigned int get_length();
	inline unsigned int get_height();

	inline bool set_height(unsigned int new_height);
	inline bool set_width(unsigned int new_width);

	inline unsigned int get_bit_depth();
	inline bool set_depth(unsigned int new_depth);

	inline bool set_color_space(std::string color_space_name_string);
	inline string get_color_space_type_name();


	pixblock();
private:

	unsigned int height;
	unsigned int width;

	unsigned int actual_height;
	unsigned int actual_width;

	unsigned int bit_depth;

	color_space * current_color_space;

	unsigned long * * pixel_block;
	pixrow pixel_row_access_buffer;
	
};

template <typename T, typename func_type>
class work_item_map
{
public:
	bool add_item(std::string name, func_type func_for_constructor);
	bool remove_item(std::string name);

	T * get_item(std::string name);

private:
	std::string type_for_map;

	std::map<std::string, func_type> work_item_map;



};

template <typename T>
class stack
{
public:
	unsigned int add_item(T * item);
	bool remove_item(unsigned int item_index);
	T * get_item(unsigned int item_index);

private:
	std::string type_for_stack;

	std::vector<T *> stack_object_vector;

};

/*class file_stack
{

};

class image_stack
{


};*/

class tool
{
public:
	inline void operator(std::stringstream * params);
private:
	std::string tool_name;

	tool_function func_from_dll;
};

/*class tool_map
{
public:

private:
	std::map<string, tool> tool_map;

};*/

class mangler
{
public:
	inline void operator(pixblock * image, std::stringstream * params);

private:
	std::string mang_name;

	mang_function func_from_dll;
};

/*class mang_script_map
{

};*/

class codec
{
public:
	inline pixblock * operator(file * file_to_decode, std::stringstream * params);
private:
	std::string code_name;

	codec_function func_from_dll;
};

/*class codec_map
{

};*/

class map_populator
{

};