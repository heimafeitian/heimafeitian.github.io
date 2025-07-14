00 AMX  
https://www.intel.com/content/www/us/en/customer-spotlight/stories/meituan-vision-ai-customer-story.html
https://www.intel.com/content/www/us/en/developer/articles/technical/accelerate-tensorflow-ml-performance-amx.html
https://www.intel.com/content/www/us/en/developer/articles/technical/accelerate-pytorch-training-inference-on-amx.html?wapkw=AMX#gs.057eia
https://www.intel.com/content/www/us/en/products/docs/accelerator-engines/what-is-intel-amx.html?wapkw=AMX
https://www.intel.com/content/www/us/en/products/docs/accelerator-engines/advanced-matrix-extensions/overview-video.html
https://www.intel.com/content/www/us/en/developer/articles/guide/bert-ai-inference-amx-4th-gen-xeon-scalable.html?wapkw=Intel%C2%AE%20Advanced%20Matrix%20Extensions
https://www.intel.com/content/www/us/en/developer/articles/technical/tuning-guide-for-ai-on-the-4th-generation.html?wapkw=%20AI%20on%204th%20Gen%20Intel%20Xeon%20Scalable%20processors%20tuning%20guide
https://www.intel.com/content/www/us/en/developer/articles/technical/tuning-guide-for-ai-on-the-4th-generation.html
intel AMX Support Lands For Linux 5.16
https://www.phoronix.com/news/Intel-AMX-Lands-In-Linux


22-cmf-225-verify-xeon-built-in-ai-acceleration-technology-amx-helps-baidu-ernie-tiny-boost-performance-by-up-to-2.66x-1129update-white-pape.pdf
2023.11_Intel SPR AMX & Perf.pptx
2023-Tech-Connect-DCAI-Bring-AMX-to-Life-Get-Most-Out-Through Software.pdf
772231-SPR AMX freq characteristics v1.0.pdf
784471_AI Acceleration using Intel AMX-TMUL.pdf
Accelerate AI Workloads with Intel AMX_update.pdf
accelerate-ai-with-amx-sb.pdf
amx-enhances-ai-inference-performance-alibaba-brief-pdf.pdf
amx-qucik-start-guide.pdf
i360_23-Enabling Your Customers to Build-and Deploy-AI-Everywhere.pdf
Intel AMX Technology Brief.pdf


01 QAT /

00 Quick StartGuide
01 QAT Document
01 QAT Technology and Roadmap
02 QAT Hardware
02 QAT Applications
03 Customer Enable
04 Competition and Performance
05 QAT Solution
06 QAT WhitePaper
07 PRC QAT IRF
08 Crypto NI
330684-011-intel-qat-api-programmers-guide.pdf
330687qatperformanceoptimizationguiderev007us.pdf
330689 IntelQAT Virtualization AppNote Rev015.pdf
336210_Intel QAT -- CE PG_rev030.pdf
336211_Intel QAT -- CE RN_rev036.pdf
336211_QAT_Software_for_Linux-Customer_Enabling_Release_Notes-rev033_rc00005.pdf
336212_Intel QAT- GSG_rev015.pdf
337003-001-intelquickassisttechnologyandopenssl-110.pdf
337002-003-qatwcontaineranddocker.pdf
549027-1.0-Intel QuickAssist_MOW-2024-WW01.pdf
571081-571081-enabling-kpt-in-nginx-openssl-rev-02.pdf
613626--1.4.0-intel--qat-programmers-guide-v1.8.pdf
621658--1--4--qat-debugging-guide.pd
Intel® QuickAssist Technology Cryptographic .pdf
qadcapiv213public .pdf

709193_qat_quick_start_guide_007.pdf

00 Nginx
01 Linux upstream
02 Openssl
03 QAT Engine
04 QATZip
05 TLS
06 IPSEC
07 CDN
08 KPT
09 ZSTD
10 QATlib
11 QUIC
12 PQC
BigData
brotli
Compression
Haproxy
SMx
Storage


ngine Development:

Develop the custom engine implementation as a separate shared library, following the OpenSSL Engine API.
Implement the necessary Engine API functions in the custom engine library, including initialization, cleanup, binding, and cryptographic operations.
Load the Engine in Your Application:

In your application code, before using any OpenSSL functions, load the custom engine using the OpenSSL function ENGINE_by_id().
Pass the unique identifier of your custom engine to ENGINE_by_id() to obtain a pointer to the ENGINE structure representing the loaded engine.
If the ENGINE_by_id() call returns NULL, it means the engine could not be loaded or is not available.
Initialize and Use the Engine:

Once you have a pointer to the ENGINE structure representing the loaded engine, initialize it by calling ENGINE_init().
Use the returned ENGINE pointer to bind the engine to OpenSSL using ENGINE_set_default(), or explicitly specify the engine in OpenSSL function calls using EVP_PKEY_CTX_set0_engine() or similar functions.
You can now use the engine for cryptographic operations, and OpenSSL will utilize your custom engine's implementation.
Cleanup:

When you're done using the custom engine, release the resources by calling ENGINE_finish() to shut down the engine.
Optionally, you can unload the engine from memory using ENGINE_free().
By following these steps, you can dynamically load and utilize your custom engine directly within your application, without relying on the OpenSSL configuration file. Ensure proper error handling and resource management throughout the process to ensure a smooth integration.

static ENGINE *try_load_engine(const char *engine)
{
    ENGINE *e = NULL;

    if ((e = ENGINE_by_id("dynamic")) != NULL) {
        if (!ENGINE_ctrl_cmd_string(e, "SO_PATH", engine, 0)
            || !ENGINE_ctrl_cmd_string(e, "LOAD", NULL, 0)) {
            ENGINE_free(e);
            e = NULL;
        }
    }
    return e;
}




    ENGINE *e = ENGINE_by_id("dynamic");
    ENGINE_ctrl_cmd_string(e, "SO_PATH", "/lib/libfoo.so", 0);
    ENGINE_ctrl_cmd_string(e, "ID", "foo", 0);
    ENGINE_ctrl_cmd_string(e, "LOAD", NULL, 0);
    ENGINE_ctrl_cmd_string(e, "CMD_FOO", "some input data", 0);



02 DLB  
03 DSA  
04 IAA  
05 AES  
06 ISA-L  
07 HSDLB  
09 AVX512_GFNI  
10 vRANBoost
