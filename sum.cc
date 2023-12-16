#include <node_api.h>

#define NAPI_CALL(env, call)                                      \
  do                                                              \
  {                                                               \
    napi_status status = (call);                                  \
    if (status != napi_ok)                                        \
    {                                                             \
      const napi_extended_error_info *error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      if (!is_pending)                                            \
      {                                                           \
        const char *message = (error_info->error_message == NULL) \
                                  ? "empty error message"         \
                                  : error_info->error_message;    \
        napi_throw_error((env), NULL, message);                   \
        return NULL;                                              \
      }                                                           \
    }                                                             \
  } while (0)



// This is the C function
// We can write our logic in C and wrap around the init node_api function
double add(double x, double y) {
  return x + y;
}

napi_value Sum(napi_env env, napi_callback_info info)
{
  size_t argc = 2;
  napi_value args[2];
  napi_value output;

  NAPI_CALL(env,napi_get_cb_info(env, info, &argc, args, NULL, NULL));

  // Read Values
  double one;
  double two;
  NAPI_CALL(env,napi_get_value_double(env, args[0], &one));
  NAPI_CALL(env,napi_get_value_double(env, args[1], &two));

  // Call the written C code
  NAPI_CALL(env,napi_create_double(env, add(one, two), &output));
  
  return output;
}

napi_value init(napi_env env, napi_value exports)
{
  napi_value sum;
  napi_create_function(env, nullptr, NAPI_AUTO_LENGTH, Sum, nullptr, &sum);
  return sum;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);