#include <node_api.h>
#include <stdio.h>
#include "test.h"

napi_value GetJD(napi_env env, napi_callback_info info) {
  napi_status status;
  // argument count
  size_t argc = 4;
  napi_value argv[4];

  // where we will store out argument values.
  int yy = 0; // year
  int mm = 0; // month
  int dd = 0; // day
  double UT = 0; // time

  // fetch arguments
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  // convert our arguments from a javascript value to C values.
  status = napi_get_value_int32(env, argv[0], &yy);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
  status = napi_get_value_int32(env, argv[1], &mm);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
  status = napi_get_value_int32(env, argv[2], &dd);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
  status = napi_get_value_double(env, argv[3], &UT);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }

  // initialize the return value as a javascript value.
  napi_value JD;

  double result = get_julian_date(yy, mm, dd, UT);

  // convert result to a javascript value
  status = napi_create_double(env, result, &JD);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return JD;

}

napi_value MyFunction(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 2;
  int number = 0;
  int number2 = 0;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  status = napi_get_value_int32(env, argv[0], &number);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }

  status = napi_get_value_int32(env, argv[1], &number2);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }

  napi_value myNumber;
  number = number * number2;

  status = napi_create_int32(env, number, &myNumber);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return myNumber;
}



napi_value getMathed(napi_env env, napi_callback_info info)
{
  int a = 0;
  int b = 0;
  int c = 0;
  napi_status status;
  size_t argc = 3;
  napi_value argv[3];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  status = napi_get_value_int32(env, argv[0], &a);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
    printf("a = %i\n", a);
  status = napi_get_value_int32(env, argv[1], &b);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
  printf("b = %i\n", b);
  status = napi_get_value_int32(env, argv[2], &c);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
  printf("c = %i\n", c);

  napi_value result2;
  int result = getMultiplied(a, b, c);

  status = napi_create_int32(env, result, &result2);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return (result2);
}


napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn1;
  napi_value fn2;
  napi_value fn3;

  status = napi_create_function(env, NULL, 0, MyFunction, NULL, &fn1);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_create_function(env, NULL, 0, getMathed, NULL, &fn2);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_create_function(env, NULL, 0, GetJD, NULL, &fn3);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }


  status = napi_set_named_property(env, exports, "my_function", fn1);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  status = napi_set_named_property(env, exports, "get_mathed", fn2);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  status = napi_set_named_property(env, exports, "get_jd", fn3);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
