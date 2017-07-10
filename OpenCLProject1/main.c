// OpenCL_Test1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "CL\opencl.h"

typedef struct
{
  /*inputs*/
  char *strPfrmName;
  uint8_t u8PfmIndx;
  
  uint8_t u8KrnlArgCnt;
  void **ptr_memHost;
  cl_mem_flags *ptr_memDevFlgs;
  size_t *ptr_memSz;

  /*platform related internals*/
  cl_context ctxID;
  cl_device_id *ptr_devices;
  cl_uint uDeviceCount;

  /*host to device communication path*/
  cl_command_queue *ptr_cmdQs;

  cl_mem *ptr_memDev;
  
  /*kernel related internals*/
  cl_program pgmID;

  cl_kernel krnID;
}tagCL_KERNEL;

typedef struct
{
  cl_platform_id pfmID;
  cl_device_id *ptr_devices;
  cl_uint uDeviceCount;
}tagCL_PLATFORM;

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
      for (size_t j = 0; j < szReturn / sizeof(size_t); j++)
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
      printf("0x%08X\n", *(cl_uint*)buffer);
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

tagCL_PLATFORM *gptr_platforms;
cl_uint gclPlatformCount;
tagCL_KERNEL gKernel1;
cl_int nErrCde;

cl_context acc_create_context(char *strPlatformName, cl_uint uDeviceCount, tagCL_KERNEL *ptrkrnlVal)
{
  for (size_t i = 0; i < gclPlatformCount; i++)
  {
    char strTemp[128];

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_NAME, 128, strTemp, NULL);
    if (strstr(strTemp, strPlatformName))
    {
      cl_context_properties properties[3] =
      {
        CL_CONTEXT_PLATFORM, (cl_context_properties)gptr_platforms[i].pfmID,
        (cl_context_properties)NULL
      };

      //found the match
      if (ptrkrnlVal)
      {
        ptrkrnlVal->u8PfmIndx = i;
        ptrkrnlVal->ctxID = clCreateContext(properties, uDeviceCount, gptr_platforms[i].ptr_devices, NULL, NULL, NULL);

        ptrkrnlVal->ptr_devices = malloc(sizeof(cl_device_id) * uDeviceCount);
        clGetContextInfo(ptrkrnlVal->ctxID, CL_CONTEXT_DEVICES, sizeof(cl_device_id) * uDeviceCount, ptrkrnlVal->ptr_devices, NULL);

        ptrkrnlVal->ptr_cmdQs = malloc(sizeof(cl_command_queue) * uDeviceCount);
        for (size_t j = 0; j < uDeviceCount; j++)
        {
          ptrkrnlVal->ptr_cmdQs[j] = clCreateCommandQueueWithProperties(ptrkrnlVal->ctxID, ptrkrnlVal->ptr_devices[j], NULL, &nErrCde);
          if (nErrCde != CL_SUCCESS)
          {
            printf("Command Q creation Failed: %d\n", nErrCde);
            break;
          }
        }

        return ptrkrnlVal->ctxID;
      }

      return clCreateContext(properties, uDeviceCount, gptr_platforms[i].ptr_devices, NULL, NULL, NULL);
    }
  }

  return NULL;
}

#if 0
/*
* Create OpenCL buffers from host memory
* These buffers will be used later by the OpenCL kernel
*/
int CreateBufferArguments(ocl_args_d_t *ocl, cl_int* inputA, cl_int* inputB, cl_int* outputC, cl_uint arrayWidth, cl_uint arrayHeight)
{
  cl_int err = CL_SUCCESS;

  // Create new OpenCL buffer objects
  // As these buffer are used only for read by the kernel, you are recommended to create it with flag CL_MEM_READ_ONLY.
  // Always set minimal read/write flags for buffers, it may lead to better performance because it allows runtime
  // to better organize data copying.
  // You use CL_MEM_COPY_HOST_PTR here, because the buffers should be populated with bytes at inputA and inputB.

  ocl->srcA = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(cl_uint) * arrayWidth * arrayHeight, inputA, &err);
  if (CL_SUCCESS != err)
  {
    LogError("Error: clCreateBuffer for srcA returned %s\n", TranslateOpenCLError(err));
    return err;
  }

  ocl->srcB = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(cl_uint) * arrayWidth * arrayHeight, inputB, &err);
  if (CL_SUCCESS != err)
  {
    LogError("Error: clCreateBuffer for srcB returned %s\n", TranslateOpenCLError(err));
    return err;
  }

  // If the output buffer is created directly on top of output buffer using CL_MEM_USE_HOST_PTR,
  // then, depending on the OpenCL runtime implementation and hardware capabilities, 
  // it may save you not necessary data copying.
  // As it is known that output buffer will be write only, you explicitly declare it using CL_MEM_WRITE_ONLY.
  ocl->dstMem = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(cl_uint) * arrayWidth * arrayHeight, outputC, &err);
  if (CL_SUCCESS != err)
  {
    LogError("Error: clCreateBuffer for dstMem returned %s\n", TranslateOpenCLError(err));
    return err;
  }


  return CL_SUCCESS;
}

/*
* Set kernel arguments
*/
cl_uint SetKernelArguments(ocl_args_d_t *ocl)
{
  cl_int err = CL_SUCCESS;

  err = clSetKernelArg(ocl->kernel, 0, sizeof(cl_mem), (void *)&ocl->srcA);
  if (CL_SUCCESS != err)
  {
    LogError("error: Failed to set argument srcA, returned %s\n", TranslateOpenCLError(err));
    return err;
  }

  err = clSetKernelArg(ocl->kernel, 1, sizeof(cl_mem), (void *)&ocl->srcB);
  if (CL_SUCCESS != err)
  {
    LogError("Error: Failed to set argument srcB, returned %s\n", TranslateOpenCLError(err));
    return err;
  }

  err = clSetKernelArg(ocl->kernel, 2, sizeof(cl_mem), (void *)&ocl->dstMem);
  if (CL_SUCCESS != err)
  {
    LogError("Error: Failed to set argument dstMem, returned %s\n", TranslateOpenCLError(err));
    return err;
  }

  return err;
}
#endif

cl_uint acc_exec_kernel(tagCL_KERNEL *ptrkrnVal, cl_uint width, cl_uint height)
{
  cl_int err = CL_SUCCESS;

  //OpenCL_host_2_device_exchange_global_memory_mapping_and_allocation
  ptrkrnVal->ptr_memDev = (void*)malloc(sizeof(cl_mem) * ptrkrnVal->u8KrnlArgCnt);
  for (size_t i = 0; i < ptrkrnVal->u8KrnlArgCnt; i++)
  {
    ptrkrnVal->ptr_memDev[i] = clCreateBuffer(ptrkrnVal->ctxID, ptrkrnVal->ptr_memDevFlgs[i], ptrkrnVal->ptr_memSz[i], ptrkrnVal->ptr_memHost[i], &err);
    if (CL_SUCCESS != err)
    {
      printf("Error: clCreateBuffer for %d returned %d\n", i, err);
      return err;
    }

    //set the kernel argurment
    err = clSetKernelArg(ptrkrnVal->krnID, i, sizeof(cl_mem), (void *)&ptrkrnVal->ptr_memDev[i]);
    if (CL_SUCCESS != err)
    {
      printf("error: Failed to set argument for %d, returned %d\n", i, err);
      return err;
    }

    //transfer the data from host to device
    if (ptrkrnVal->ptr_memDevFlgs[i] & (CL_MEM_READ_ONLY |CL_MEM_READ_WRITE))
    {
      err = clEnqueueWriteBuffer(ptrkrnVal->ptr_cmdQs[0], ptrkrnVal->ptr_memDev[i], CL_TRUE, 0, ptrkrnVal->ptr_memSz[i], ptrkrnVal->ptr_memHost[i], 0, NULL, NULL);
      if (CL_SUCCESS != err)
      {
        printf("Error: clEnqueueWriteBuffer for %d returned %d\n", i, err);
        return err;
      }
    }
  }

  // Define global iteration space for clEnqueueNDRangeKernel.
  size_t globalWorkSize[2] = { width, height };
  size_t localWorkSize[2] = { 1, 1 };

  // execute kernel
  err = clEnqueueNDRangeKernel(ptrkrnVal->ptr_cmdQs[0], ptrkrnVal->krnID, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
  if (CL_SUCCESS != err)
  {
    printf("Error: Failed to run kernel, return %d\n", (err));
    return err;
  }

  // Wait until the queued kernel is completed by the device
  err = clFinish(ptrkrnVal->ptr_cmdQs[0]);
  if (CL_SUCCESS != err)
  {
    printf("Error: clFinish 1 return %d\n", (err));
    return err;
  }

  for (size_t i = 0; i < ptrkrnVal->u8KrnlArgCnt; i++)
  {
    //transfer the data from device to host
    if (ptrkrnVal->ptr_memDevFlgs[i] & (CL_MEM_WRITE_ONLY|CL_MEM_READ_WRITE))
    {
      err = clEnqueueReadBuffer(ptrkrnVal->ptr_cmdQs[0], ptrkrnVal->ptr_memDev[i], CL_TRUE, 0, ptrkrnVal->ptr_memSz[i], ptrkrnVal->ptr_memHost[i], 0, NULL, NULL);

      if (CL_SUCCESS != err)
      {
        printf("Error: clEnqueueWriteBuffer for %d returned %d\n", i, err);
        return err;
      }
    }
  }

  // Wait until the queued kernel is completed by the device
  err = clFinish(ptrkrnVal->ptr_cmdQs[0]);
  if (CL_SUCCESS != err)
  {
    printf("Error: clFinish 2 return %d\n", (err));
    return err;
  }

  //TODO: fix the memory leak
  free(ptrkrnVal->ptr_memDev);

  return CL_SUCCESS;
}

void acc_load_kernel(char *strFilePath, char *strOptions, tagCL_KERNEL *ptrkrnVal)
{
  char *strSource;
  size_t arrszFileLength[2] = { 0 };
  cl_int nErrCde;

  FILE *hFile = fopen(strFilePath, "r");

  fseek(hFile, 0, SEEK_END);
  arrszFileLength[0] = ftell(hFile);
  fseek(hFile, 0, SEEK_SET);

  strSource = (void *)malloc(arrszFileLength[0]);
  fread(strSource, sizeof(char), arrszFileLength[0], hFile);

  acc_create_context(ptrkrnVal->strPfrmName, ptrkrnVal->uDeviceCount, ptrkrnVal);

  ptrkrnVal->pgmID = clCreateProgramWithSource(ptrkrnVal->ctxID, ptrkrnVal->uDeviceCount, &strSource, arrszFileLength, &nErrCde);
  free(strSource);
  if (nErrCde == CL_SUCCESS)
  {
    //build kernel for all the devices
    nErrCde = clBuildProgram(ptrkrnVal->pgmID, 0, NULL, strOptions, NULL, NULL);
    if (nErrCde == CL_SUCCESS)
    {
      ptrkrnVal->krnID = clCreateKernel(ptrkrnVal->pgmID, "Add", &nErrCde);
    }
    else
    {
      printf("Kernel Building failed: %d\n", nErrCde);
      size_t log_size = 0;
      clGetProgramBuildInfo(ptrkrnVal->pgmID, ptrkrnVal->ptr_devices[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

      char *build_log = (void *)malloc(log_size);
      clGetProgramBuildInfo(ptrkrnVal->pgmID, ptrkrnVal->ptr_devices[0], CL_PROGRAM_BUILD_LOG, log_size, &build_log[0], NULL);
      printf(build_log);
      free(build_log);
    }
  }
  else
  {
    printf("Kernel Source code loading failed: %d\n", nErrCde);
  }

  fclose(hFile);
}

void acc_init(void)
{
  //get the platform count
  clGetPlatformIDs(0, NULL, &gclPlatformCount);
  cl_platform_id *platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * gclPlatformCount);
  gptr_platforms = (tagCL_PLATFORM*)malloc(sizeof(tagCL_PLATFORM) * gclPlatformCount);

  //get the platform ids
  clGetPlatformIDs(gclPlatformCount, platforms, NULL);
  for (size_t i = 0; i < gclPlatformCount; i++)
  {
    gptr_platforms[i].pfmID = platforms[i];

    //get the device count from each platform
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &gptr_platforms[i].uDeviceCount);

    //get the device ids list
    gptr_platforms[i].ptr_devices = (cl_device_id*)malloc(sizeof(cl_device_id) * gptr_platforms[i].uDeviceCount);
    clGetDeviceIDs(gptr_platforms[i].pfmID, CL_DEVICE_TYPE_ALL, gptr_platforms[i].uDeviceCount, gptr_platforms[i].ptr_devices, NULL);
  }

  free(platforms);
}

void acc_uninit(void)
{
  for (size_t i = 0; i < gclPlatformCount; i++)
  {
    free(gptr_platforms[i].ptr_devices);
  }
  free(gptr_platforms);
}

void acc_print_information(void)
{
  printf("Total No.Of Platform: %u\n", gclPlatformCount);

  for (size_t i = 0; i < gclPlatformCount; i++)
  {
    char strTemp[128];
    cl_ulong ulTemp;

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_PROFILE, 128, strTemp, NULL);
    printf("\nCL_PLATFORM_PROFILE : %s\n", strTemp);

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_VERSION, 128, strTemp, NULL);
    printf("CL_PLATFORM_VERSION : %s\n", strTemp);

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_NAME, 128, strTemp, NULL);
    printf("CL_PLATFORM_NAME: %s\n", strTemp);

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_VENDOR, 128, strTemp, NULL);
    printf("CL_PLATFORM_VENDOR: %s\n", strTemp);

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_EXTENSIONS, 128, strTemp, NULL);
    printf("CL_PLATFORM_EXTENSIONS: %s\n", strTemp);

    clGetPlatformInfo(gptr_platforms[i].pfmID, CL_PLATFORM_HOST_TIMER_RESOLUTION, sizeof(ulTemp), &ulTemp, NULL);
    printf("CL_PLATFORM_HOST_TIMER_RESOLUTION: %llu\n", ulTemp);

    for (size_t j = 0; j < gptr_platforms[i].uDeviceCount; j++)
    {
      printf("Device %u of %u\n", j + 1, gptr_platforms[i].uDeviceCount);
      _print_device_info(gptr_platforms[i].ptr_devices[j]);
    }
  }
}

int main()
{
  acc_init();

  //acc_print_information();

  tagCL_KERNEL myKernel = { 0 };
  myKernel.strPfrmName = "Intel(R) OpenCL";
  myKernel.uDeviceCount = 1;
  
  acc_load_kernel("D:\\prj\\OpenCLProject1\\OpenCLProject1\\Template.cl", "", &myKernel);

  const int elmsz = 8;

  cl_mem_flags tmpFlgs[3] = { CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR , CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR , CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR };
  size_t tmpSz[3] = { elmsz, elmsz, elmsz };
  cl_int *tmpHostBuff[3];

  tmpHostBuff[0] = (void*)_aligned_malloc(sizeof(cl_int) * tmpSz[0], 4096);
  tmpHostBuff[1] = (void*)_aligned_malloc(sizeof(cl_int) * tmpSz[1], 4096);
  tmpHostBuff[2] = (void*)_aligned_malloc(sizeof(cl_int) * tmpSz[2], 4096);

  myKernel.u8KrnlArgCnt = 3;
  myKernel.ptr_memSz = tmpSz;
  myKernel.ptr_memDevFlgs = tmpFlgs;
  myKernel.ptr_memHost = (void*)tmpHostBuff;

  for (size_t i = 0; i < elmsz; i++)
  {
    *(tmpHostBuff[0] + i) = i; *(tmpHostBuff[1] + i) = i+1; *(tmpHostBuff[2] + i) = 0;
  }

  printf("Before Kernel execution\n");
  for (size_t i = 0; i < elmsz; i++)
  {
    printf("%d+%d=%d\n", *(tmpHostBuff[0] + i), *(tmpHostBuff[1] + i), *(tmpHostBuff[2] + i));
  }

  acc_exec_kernel(&myKernel, elmsz, elmsz);

  printf("After Kernel execution\n");
  for (size_t i = 0; i < elmsz; i++)
  {
    printf("%d+%d=%d\n", *(tmpHostBuff[0] + i), *(tmpHostBuff[1] + i), *(tmpHostBuff[2] + i));
  }

  _aligned_free(tmpHostBuff[0]);
  _aligned_free(tmpHostBuff[1]);
  _aligned_free(tmpHostBuff[2]);

  if (myKernel.krnID)
    clReleaseKernel(myKernel.krnID);

  if (myKernel.pgmID)
    clReleaseProgram(myKernel.pgmID);

  if (myKernel.ptr_cmdQs)
  {
    for (size_t i = 0; i < myKernel.uDeviceCount; i++)
    {
      clReleaseCommandQueue(myKernel.ptr_cmdQs[i]);
    }
    free(myKernel.ptr_cmdQs);
  }

  if (myKernel.ptr_devices)
    free(myKernel.ptr_devices);

  if (myKernel.ctxID)
    clReleaseContext(myKernel.ctxID);

  acc_uninit();

  return 0;
}

