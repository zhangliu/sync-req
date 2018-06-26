#include <stdio.h>
#include <curl/curl.h>

namespace sr_curl
{
// const char *post(const char *url, const char *data)
// {
//   CURL *curl;
//   CURLcode res;

//   // curl_global_init(CURL_GLOBAL_ALL);
//   curl = curl_easy_init();

//   if (curl)
//   {
//     curl_easy_setopt(curl, CURLOPT_URL, url);
//     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

//     res = curl_easy_perform(curl);
//     if (res != CURLE_OK)
//     {
//       char *msg;
//       sprintf(msg, "%s", curl_easy_strerror(res));
//       return msg;
//     }

//     curl_easy_cleanup(curl);
//   }
//   // curl_global_cleanup();
//   return "ok";
// }

struct MemoryStruct
{
  char *memory;
  size_t size;
};

const char *upload(const char *url, const char *filePath)
{
  CURL *curl;
  CURLcode res;
  char *errMsg = NULL;
  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct MemoryStruct chunk;

  // curl_global_init(CURL_GLOBAL_ALL);

  curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "files", CURLFORM_FILE, filePath, CURLFORM_END);

  curl = curl_easy_init();
  if (!curl)
    return "无法构建curl对象";

  // 解决100-continue问题
  struct curl_slist *headers = 0;
  headers = curl_slist_append(headers, "Expect:");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
  // TODO get response body, see: https://curl.haxx.se/libcurl/c/getinmemory.html
  // curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

  res = curl_easy_perform(curl);

  // 释放资源
  curl_easy_cleanup(curl);
  curl_formfree(formpost);
  curl_slist_free_all(headers);

  if (res != CURLE_OK)
  {
    sprintf(errMsg, "%s", curl_easy_strerror(res));
    return errMsg;
  }
  return "ok";
}
} // namespace sr_curl