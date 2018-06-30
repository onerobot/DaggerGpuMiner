mac support:
1 new xcode project, add files
2 config xcode project: add User Header Search Paths: $(PROJECT_DIR)/../GpuMiner ; add OpenCL.framework
3 install boost
4 cofing xcode project: add Header Search Paths: /usr/local/include ; and Library Search Paths: /usr/local/lib ; and libboost_system.a
5 modify code: add all __APPLE__ macro
6 add Launch Arguments: -cpu -a G4dehJ/SzGpnPKIaAr0ass3pLadTSZLV -p cn.xdag.vspool.com:13654
