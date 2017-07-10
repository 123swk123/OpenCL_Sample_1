// OpenCL_Test1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "CL\opencl.h"

typedef enum
{
  type_cl_uint,
  type_cl_bool,
  type_char_arr,
  type_cl_device_fp_config,
  type_cl_device_exec_capabilities,
  type_cl_ulong,
  type_cl_device_mem_cache_type,
  type_size_t,
  type_cl_device_local_mem_type,
  type_size_t_arr,
  type_cl_device_id,
  type_cl_device_affinity_domain,
  type_cl_device_partition_property_arr,
  type_cl_platform_id,
  type_cl_command_queue_properties,
  type_cl_device_svm_capabilities,
  type_cl_device_terminate_capability_khr,
  type_cl_device_type
}TST_TYPES;

typedef struct
{
  int nParamName;
  char *strParamName;
  size_t szParam;
  TST_TYPES nDataType;
}TST_STRUCT;

TST_STRUCT DEVICE_DETAILS[] =
{
  { CL_DEVICE_ADDRESS_BITS,"CL_DEVICE_ADDRESS_BITS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_AVAILABLE,"CL_DEVICE_AVAILABLE",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_BUILT_IN_KERNELS,"CL_DEVICE_BUILT_IN_KERNELS",1024,type_char_arr },
  { CL_DEVICE_COMPILER_AVAILABLE,"CL_DEVICE_COMPILER_AVAILABLE",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_DOUBLE_FP_CONFIG,"CL_DEVICE_DOUBLE_FP_CONFIG",sizeof(cl_device_fp_config),type_cl_device_fp_config },
  { CL_DEVICE_ENDIAN_LITTLE,"CL_DEVICE_ENDIAN_LITTLE",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_ERROR_CORRECTION_SUPPORT,"CL_DEVICE_ERROR_CORRECTION_SUPPORT",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_EXECUTION_CAPABILITIES,"CL_DEVICE_EXECUTION_CAPABILITIES",sizeof(cl_device_exec_capabilities),type_cl_device_exec_capabilities },
  { CL_DEVICE_EXTENSIONS,"CL_DEVICE_EXTENSIONS",1024,type_char_arr },
  { CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,"CL_DEVICE_GLOBAL_MEM_CACHE_SIZE",sizeof(cl_ulong),type_cl_ulong },
  { CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,"CL_DEVICE_GLOBAL_MEM_CACHE_TYPE",sizeof(cl_device_mem_cache_type),type_cl_device_mem_cache_type },
  { CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,"CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_GLOBAL_MEM_SIZE,"CL_DEVICE_GLOBAL_MEM_SIZE",sizeof(cl_ulong),type_cl_ulong },
  { CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE,"CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_IL_VERSION,"CL_DEVICE_IL_VERSION",1024,type_char_arr },
  { CL_DEVICE_IMAGE2D_MAX_HEIGHT,"CL_DEVICE_IMAGE2D_MAX_HEIGHT",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE2D_MAX_WIDTH,"CL_DEVICE_IMAGE2D_MAX_WIDTH",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE3D_MAX_DEPTH,"CL_DEVICE_IMAGE3D_MAX_DEPTH",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE3D_MAX_HEIGHT,"CL_DEVICE_IMAGE3D_MAX_HEIGHT",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE3D_MAX_WIDTH,"CL_DEVICE_IMAGE3D_MAX_WIDTH",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT,"CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_IMAGE_MAX_ARRAY_SIZE,"CL_DEVICE_IMAGE_MAX_ARRAY_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE_MAX_BUFFER_SIZE,"CL_DEVICE_IMAGE_MAX_BUFFER_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_IMAGE_PITCH_ALIGNMENT,"CL_DEVICE_IMAGE_PITCH_ALIGNMENT",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_IMAGE_SUPPORT,"CL_DEVICE_IMAGE_SUPPORT",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_LINKER_AVAILABLE,"CL_DEVICE_LINKER_AVAILABLE",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_LOCAL_MEM_SIZE,"CL_DEVICE_LOCAL_MEM_SIZE",sizeof(cl_ulong),type_cl_ulong },
  { CL_DEVICE_LOCAL_MEM_TYPE,"CL_DEVICE_LOCAL_MEM_TYPE",sizeof(cl_device_local_mem_type),type_cl_device_local_mem_type },
  { CL_DEVICE_MAX_CLOCK_FREQUENCY,"CL_DEVICE_MAX_CLOCK_FREQUENCY",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_COMPUTE_UNITS,"CL_DEVICE_MAX_COMPUTE_UNITS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_CONSTANT_ARGS,"CL_DEVICE_MAX_CONSTANT_ARGS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,"CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE",sizeof(cl_ulong),type_cl_ulong },
  { CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE,"CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_MAX_MEM_ALLOC_SIZE,"CL_DEVICE_MAX_MEM_ALLOC_SIZE",sizeof(cl_ulong),type_cl_ulong },
  { CL_DEVICE_MAX_NUM_SUB_GROUPS,"CL_DEVICE_MAX_NUM_SUB_GROUPS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_ON_DEVICE_EVENTS,"CL_DEVICE_MAX_ON_DEVICE_EVENTS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_ON_DEVICE_QUEUES,"CL_DEVICE_MAX_ON_DEVICE_QUEUES",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_PARAMETER_SIZE,"CL_DEVICE_MAX_PARAMETER_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_MAX_PIPE_ARGS,"CL_DEVICE_MAX_PIPE_ARGS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_READ_IMAGE_ARGS,"CL_DEVICE_MAX_READ_IMAGE_ARGS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS,"CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_SAMPLERS,"CL_DEVICE_MAX_SAMPLERS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_WORK_GROUP_SIZE,"CL_DEVICE_MAX_WORK_GROUP_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,"CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MAX_WORK_ITEM_SIZES,"CL_DEVICE_MAX_WORK_ITEM_SIZES",1024,type_size_t_arr },
  { CL_DEVICE_MAX_WRITE_IMAGE_ARGS,"CL_DEVICE_MAX_WRITE_IMAGE_ARGS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_MEM_BASE_ADDR_ALIGN,"CL_DEVICE_MEM_BASE_ADDR_ALIGN",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_NAME,"CL_DEVICE_NAME",1024,type_char_arr },
  //{ CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR                      CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT                      CL_DEVICE_NATIVE_VECTOR_WIDTH_INT                      CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG                      CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT                      CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE                      CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,"CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR                      CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT                      CL_DEVICE_NATIVE_VECTOR_WIDTH_INT                      CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG                      CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT                      CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE                      CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_OPENCL_C_VERSION,"CL_DEVICE_OPENCL_C_VERSION",1024,type_char_arr },
  { CL_DEVICE_PARENT_DEVICE,"CL_DEVICE_PARENT_DEVICE",sizeof(cl_device_id),type_cl_device_id },
  { CL_DEVICE_PARTITION_AFFINITY_DOMAIN,"CL_DEVICE_PARTITION_AFFINITY_DOMAIN",sizeof(cl_device_affinity_domain),type_cl_device_affinity_domain },
  { CL_DEVICE_PARTITION_MAX_SUB_DEVICES,"CL_DEVICE_PARTITION_MAX_SUB_DEVICES",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_PARTITION_PROPERTIES,"CL_DEVICE_PARTITION_PROPERTIES",1024,type_cl_device_partition_property_arr },
  { CL_DEVICE_PARTITION_TYPE,"CL_DEVICE_PARTITION_TYPE",1024,type_cl_device_partition_property_arr },
  { CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS,"CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_PIPE_MAX_PACKET_SIZE,"CL_DEVICE_PIPE_MAX_PACKET_SIZE",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_PLATFORM,"CL_DEVICE_PLATFORM",sizeof(cl_platform_id),type_cl_platform_id },
  { CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT,"CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_PREFERRED_INTEROP_USER_SYNC,"CL_DEVICE_PREFERRED_INTEROP_USER_SYNC",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT,"CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT,"CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT",sizeof(cl_uint),type_cl_uint },
  //{ CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,"CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE                      CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_PRINTF_BUFFER_SIZE,"CL_DEVICE_PRINTF_BUFFER_SIZE",sizeof(size_t),type_size_t },
  { CL_DEVICE_PROFILE,"CL_DEVICE_PROFILE",1024,type_char_arr },
  { CL_DEVICE_PROFILING_TIMER_RESOLUTION,"CL_DEVICE_PROFILING_TIMER_RESOLUTION",sizeof(size_t),type_size_t },
  { CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE,"CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE,"CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES,"CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES",sizeof(cl_command_queue_properties),type_cl_command_queue_properties },
  { CL_DEVICE_QUEUE_ON_HOST_PROPERTIES,"CL_DEVICE_QUEUE_ON_HOST_PROPERTIES",sizeof(cl_command_queue_properties),type_cl_command_queue_properties },
  { CL_DEVICE_REFERENCE_COUNT,"CL_DEVICE_REFERENCE_COUNT",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_SINGLE_FP_CONFIG,"CL_DEVICE_SINGLE_FP_CONFIG",sizeof(cl_device_fp_config),type_cl_device_fp_config },
  { CL_DEVICE_SPIR_VERSIONS,"CL_DEVICE_SPIR_VERSIONS",1024,type_char_arr },
  //{ CL_DEVICE_SUBGROUP_INDEPENDENT_FORWARD_PROGRESS,"CL_DEVICE_SUBGROUP_INDEPENDENT_FORWARD_PROGRESS",sizeof(cl_bool),type_cl_bool },
  { CL_DEVICE_SVM_CAPABILITIES,"CL_DEVICE_SVM_CAPABILITIES",sizeof(cl_device_svm_capabilities),type_cl_device_svm_capabilities },
  //{ CL_DEVICE_TERMINATE - _CAPABILITY_KHR,"CL_DEVICE_TERMINATE-_CAPABILITY_KHR",sizeof(cl_device_terminate_capability_khr),type_cl_device_terminate_capability_khr },
  { CL_DEVICE_TYPE,"CL_DEVICE_TYPE",sizeof(cl_device_type),type_cl_device_type },
  { CL_DEVICE_VENDOR,"CL_DEVICE_VENDOR",1024,type_char_arr },
  { CL_DEVICE_VENDOR_ID,"CL_DEVICE_VENDOR_ID",sizeof(cl_uint),type_cl_uint },
  { CL_DEVICE_VERSION,"CL_DEVICE_VERSION",1024,type_char_arr },
  { CL_DRIVER_VERSION,"CL_DRIVER_VERSION",1024,type_char_arr }
};

void _print_device_info(cl_device_id devID)
{
  char buffer[1024];
  size_t szReturn;

  for (size_t indx = 0; indx < sizeof(DEVICE_DETAILS) / sizeof(TST_STRUCT); indx++)
  {
    clGetDeviceInfo(devID, DEVICE_DETAILS[indx].nParamName, DEVICE_DETAILS[indx].szParam, buffer, &szReturn);

    printf("\t%s:", DEVICE_DETAILS[indx].strParamName);

    switch (DEVICE_DETAILS[indx].nDataType)
    {
    case type_cl_uint:
      printf("%u\n", *(cl_uint*)buffer);
      break;
    case type_cl_bool:
      printf("%u\n", *(cl_bool*)buffer);
      break;
    case type_char_arr:
      printf("%s\n", buffer);
      break;
    case type_cl_device_fp_config:
      printf("0x%08llX\n", *(cl_device_fp_config*)buffer);
      break;
    case type_cl_device_exec_capabilities:
      printf("0x%08llX\n", *(cl_device_exec_capabilities*)buffer);
      break;
    case type_cl_ulong:
      printf("%llu\n", *(cl_ulong*)buffer);
      break;
    case type_cl_device_mem_cache_type:
      printf("0x%04X\n", *(cl_device_mem_cache_type*)buffer);
      break;
    case type_size_t:
      printf("%u\n", *(size_t*)buffer);
      break;
    case type_cl_device_local_mem_type:
      printf("0x%04X\n", *(cl_device_local_mem_type*)buffer);
      break;
    case type_size_t_arr:
      printf("\n");
      for (size_t j = 0; j < szReturn/sizeof(size_t); j++)
      {
        printf("\t\t%u:%u\n", j, *(size_t*)(buffer + (sizeof(size_t) * j)));
      }
      break;
    case type_cl_device_id:
      printf("%u\n", *(cl_uint*)buffer);
      break;
    case type_cl_device_affinity_domain:
      printf("%u\n", *(cl_uint*)buffer);
      break;
    case type_cl_device_partition_property_arr:
      printf("\n");
      for (size_t j = 0; j < szReturn / sizeof(cl_device_partition_property); j++)
      {
        printf("\t\t%u:0x%04X\n", j, *(cl_device_partition_property*)(buffer + (sizeof(cl_device_partition_property) * j)));
      }
      break;
    case type_cl_platform_id:
      printf("%u\n", *(cl_uint*)buffer);
      break;
    case type_cl_command_queue_properties:
      printf("0x%08llX\n", *(cl_command_queue_properties*)buffer);
      break;
    case type_cl_device_svm_capabilities:
      printf("0x%08llX\n", *(cl_device_svm_capabilities*)buffer);
      break;
    case type_cl_device_terminate_capability_khr:
      //printf("0x%08llX\n", *(cl_device_terminate_capability_khr*)buffer);
      break;
    case type_cl_device_type:
      printf("0x%08llX\n", *(cl_device_type*)buffer);
      break;
    }
  }
}

int main()
{
  cl_uint numPlatforms;

  clGetPlatformIDs(0, NULL, &numPlatforms);

  printf("No Of Platforms: %u\n", numPlatforms);

  cl_platform_id *platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * numPlatforms);
  clGetPlatformIDs(numPlatforms, platforms, NULL);

  for (size_t i = 0; i < numPlatforms; i++)
  {
    char strTemp[128];
    cl_ulong ulTemp;
    cl_uint unTemp;
    cl_uint unDeviceCount;
    cl_device_id *devices;

    clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 128, strTemp, NULL);
    printf("\nCL_PLATFORM_PROFILE : %s\n", strTemp);

    clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 128, strTemp, NULL);
    printf("CL_PLATFORM_VERSION : %s\n", strTemp);

    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 128, strTemp, NULL);
    printf("CL_PLATFORM_NAME: %s\n", strTemp);

    clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 128, strTemp, NULL);
    printf("CL_PLATFORM_VENDOR: %s\n", strTemp);

    clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 128, strTemp, NULL);
    printf("CL_PLATFORM_EXTENSIONS: %s\n", strTemp);

    clGetPlatformInfo(platforms[i], CL_PLATFORM_HOST_TIMER_RESOLUTION, sizeof(ulTemp), &ulTemp, NULL);
    printf("CL_PLATFORM_HOST_TIMER_RESOLUTION: %u\n", ulTemp);

    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &unDeviceCount);
    printf("Device Count: %u\n", unDeviceCount);

    devices = (cl_device_id*)malloc(sizeof(cl_device_id) * unDeviceCount);
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, unDeviceCount, devices, NULL);
    for (size_t j = 0; j < unDeviceCount; j++)
    {
      _print_device_info(devices[j]);
    }
    free(devices);
  }

  free(platforms);

  return 0;
}

