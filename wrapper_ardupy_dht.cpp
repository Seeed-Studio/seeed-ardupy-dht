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
 
 
#include "Seeed_Arduino_DHT/DHT.h" //include dependent Arduino library

extern "C" //tell compiler to use the C naming and calling conventions 
{
    //needed header files from micropython
    #include "py/mphal.h"
    #include "py/nlr.h"
    #include "py/objtype.h"
    #include "py/runtime.h"
    #include "shared-bindings/util.h"
}

//initialize module 
#define dht (*(DHT *)self->module)
void *operator new(size_t, void *);

//map functions from dependent Arduino library 
extern "C"
{
    void common_hal_dht_construct(abstract_module_t *self, int pin, int type, int count) //initializing function to create an object
    {
        if (count != -1)
        {
            self->module = new (m_new_obj(DHT)) DHT(pin, type, count); //if count is not equal to -1, pass in count parameter
        }
        else
        {
            self->module = new (m_new_obj(DHT)) DHT(pin, type); //if count is equal to -1, don't pass in count parameter
        }
        dht.begin(); //start the sensor 
    }
    void common_hal_dht_deinit(abstract_module_t *self) //deinitializing function
    {
        dht.~DHT();
    }
    float common_hal_dht_temperature(abstract_module_t *self) //function to obtain temperature readings
    {
        return dht.readTemperature();
    }  
    float common_hal_dht_humidity(abstract_module_t *self) //function to obtain humidity readings
    {
        return dht.readHumidity();
    } 
    float common_hal_dht_ctof(abstract_module_t *self, float c) //function to convert passed in celcius values to farenheit
    {
        return dht.convertCtoF(c);
    }          
}

