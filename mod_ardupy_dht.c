/**
 * The MIT License (MIT)
 *
 * Author: Lakshantha Dissanayake (lakshanthad@seeed.cc)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


//needed header files from micropython
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "shared-bindings/util.h"

//include previously defined functions from wrapper
void common_hal_dht_construct(abstract_module_t *self, int pin, int type, int count);
void common_hal_dht_deinit(abstract_module_t *self);
float common_hal_dht_temperature(abstract_module_t *self);
float common_hal_dht_humidity(abstract_module_t *self);
float common_hal_dht_ctof(abstract_module_t *self, float c);

extern const mp_obj_type_t grove_dht_type; //declaration of initial module type 

//initialize module 
m_generic_make(dht)
{
    enum //anonymous enumeration
    {
        //three parameters
        ARG_pin,
        ARG_type,
        ARG_count
    };
    static const mp_arg_t allowed_args[] = {
        {MP_QSTR_pin, MP_ARG_INT, {.u_int = -1}}, //default value is -1
        {MP_QSTR_type, MP_ARG_INT, {.u_int = -1}},
        {MP_QSTR_count, MP_ARG_INT, {.u_int = -1}},
    };

    abstract_module_t *self = new_abstruct_module(type);
    mp_arg_val_t vals[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_check_num(n_args, n_kw, 2, 3, false); //number of parameters to pass can be 2 or 3
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, vals);

    common_hal_dht_construct(self, vals[ARG_pin].u_int, vals[ARG_type].u_int, vals[ARG_count].u_int);
    return self;

}

//object attributes 
void dht_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    abstract_module_t *self = (abstract_module_t *)self_in;
    float number; //define number as float data type

    if (dest[0] == MP_OBJ_NULL) //load attributes 
    {
        if (attr == MP_QSTR_temperature) //MP_QSTR_[Function-name] & Function-name used for ArduPy calling 
        {
            number = common_hal_dht_temperature(self); //call previously defined function
            dest[0] = mp_obj_new_float(number); //this is the Micropython float type and should match with the data type 
            return;
        }
        else if (attr == MP_QSTR_humidity)
        {
            number = common_hal_dht_humidity(self);
            dest[0] = mp_obj_new_float(number);
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

//object attributes for functions that take parameters 
mp_obj_t dht_ctof(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    float c = mp_obj_get_float(pos_args[1]);
    float f = common_hal_dht_ctof(self, c);
    return mp_obj_new_float(f);
}
MP_DEFINE_CONST_FUN_OBJ_KW(dht_ctof_obj, 1, dht_ctof);

//look-up table 
const mp_rom_map_elem_t dht_locals_dict_table[] = {
    //instance methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&dht_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&dht_obj___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_ctof), MP_ROM_PTR(&dht_ctof_obj)}, //add the function with parameters
};
MP_DEFINE_CONST_DICT(dht_locals_dict, dht_locals_dict_table);

//initial module type 
const mp_obj_type_t grove_dht_type = {
    {&mp_type_type},
    .name = MP_QSTR_grove_dht,
    .make_new = dht_make_new,
    .locals_dict = (mp_obj_t)&dht_locals_dict,
    .attr = dht_obj_attr,
};