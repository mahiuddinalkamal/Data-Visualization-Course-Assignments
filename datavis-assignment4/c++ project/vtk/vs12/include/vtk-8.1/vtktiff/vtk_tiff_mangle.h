#ifndef vtk_tiff_mangle_h
#define vtk_tiff_mangle_h

/*
This header file mangles all symbols exported from the tiff library.
It is included in all files while building the tiff library.  Due to
namespace pollution, no tiff headers should be included in .h files in
VTK.

The following command was used to obtain the symbol list on macOS:

Mac: nm -g lib/libvtktiff* 2> /dev/null | grep " [TDRS] " | awk '{ print substr($3, 2); }' | awk '{ sub(/vtk_/, ""); print }' | sed 's/\(.*\)/#define \1\ vtk_\1/' | sort

The following command was used to obtain the symbol list on Linux:

Linux: nm -g lib/libvtktiff* 2> /dev/null | grep " [TDRS] " | awk '{ print $3 }' | awk '{ sub(/vtk_/, ""); print }' | sed 's/\(.*\)/#define \1\ vtk_\1/' | sort

Explanation:
1) The nm command extracts all global/external symbols from the library.
2) The grep command extracts all the public symbols from the library. (Text, Data, Read-only data, Small objects).
3) The first awk command prints out only the third column which is the symbol name (the first 2 columns are location and type) (also removes the leading underscore on macOS).
4) The second awk command prints remove any "vtk_" prefix that exists already.
5) The sed command mangles the symbols and formats the output in such a way to be copy and pasted below.
6) The sort commands sorts the lines alphabetically.

The following commands are used to generate the suggested symbols on Windows systems:

dumpbin /symbols vtktiff* > symbol_table.txt (Must be done from the Visual Studio Command Prompt)
cat symbol_table.txt | grep "External" | grep -i "TIFF" | awk '{print $(NF) }' | awk '!/vtk_/ { print }' | awk '{ if (a[$1]++ == 0) print $0; }' "$@" | sed 's \(.*\) \1\ vtk_\1 ' | sed 's/^/#define /' (Must be done in git bash)

For the bash commands:
The first command prints the symbol table
The second command extracts all the external symbols
The third command only extracts those symbols with TIFF in them (case-insensitive)
The fourth command only prints out the last column (which is the symbol name)
The fifth command only prints out those symbols which have not been mangled with vtk_ already
The sixth command removes duplicates
The seventh and eighth commmands mangles the symbols and formats the output in such a way to be easily copy and pasted below.

The developer will then need to *MANUALLY* add the symbols to the list below. Please try to keep the symbols in a sorted order (you can use sort utility, in Linux don't forget to to set environmental variable LC_COLLATE=POSIX to deal with the underscores correctly)
*/

// Section containing symbols which are conditionally defined (alphabetizied!)
#ifdef CCITT_SUPPORT
#define TIFFInitCCITTFax3 vtk_TIFFInitCCITTFax3
#define TIFFInitCCITTFax4 vtk_TIFFInitCCITTFax4
#define TIFFInitCCITTRLE vtk_TIFFInitCCITTRLE
#define TIFFInitCCITTRLEW vtk_TIFFInitCCITTRLEW
#endif

#ifdef JBIG_SUPPORT
#define TIFFInitJBIG vtk_TIFFInitJBIG
#endif

#ifdef JPEG_SUPPORT
#define TIFFInitJPEG vtk_TIFFInitJPEG
#endif

#ifdef LOGLUV_SUPPORT
#define TIFFInitSGILog vtk_TIFFInitSGILog
#endif

#ifndef LZMA_SUPPORT
#define TIFFInitLZMA vtk_TIFFInitLZMA
#endif

#ifdef LZW_SUPPORT
#define TIFFInitLZW vtk_TIFFInitLZW
#endif

#ifdef NEXT_SUPPORT
#define TIFFInitNeXT vtk_TIFFInitNeXT
#endif

#ifdef OJPEG_SUPPORT
#define TIFFInitOJPEG vtk_TIFFInitOJPEG
#endif

#ifdef PACKBITS_SUPPORT
#define TIFFInitPackBits vtk_TIFFInitPackBits
#endif

#ifdef PIXARLOG_SUPPORT
#define TIFFInitPixarLog vtk_TIFFInitPixarLog
#endif

#ifdef THUNDER_SUPPORT
#define TIFFInitThunderScan vtk_TIFFInitThunderScan
#endif

#ifdef ZIP_SUPPORT
#define TIFFInitZIP vtk_TIFFInitZIP
#endif

// Section containing symbols which are found in Linux but not in all platforms
#ifdef __linux__
#endif

// Section containing symbols which are found in Windows but not in all platforms
#ifdef _WIN32
#define TIFFOpenW vtk_TIFFOpenW
#endif

// Section containing symbols which are found in macOS but not in all platforms
#ifdef __APPLE__
#endif

// Common symbols
#define LogL10fromY vtk_LogL10fromY
#define LogL10toY vtk_LogL10toY
#define LogL16fromY vtk_LogL16fromY
#define LogL16toY vtk_LogL16toY
#define LogLuv24fromXYZ vtk_LogLuv24fromXYZ
#define LogLuv24toXYZ vtk_LogLuv24toXYZ
#define LogLuv32fromXYZ vtk_LogLuv32fromXYZ
#define LogLuv32toXYZ vtk_LogLuv32toXYZ
#define TIFFAccessTagMethods vtk_TIFFAccessTagMethods
#define TIFFCIELabToRGBInit vtk_TIFFCIELabToRGBInit
#define TIFFCIELabToXYZ vtk_TIFFCIELabToXYZ
#define TIFFCheckTile vtk_TIFFCheckTile
#define TIFFCheckpointDirectory vtk_TIFFCheckpointDirectory
#define TIFFCleanup vtk_TIFFCleanup
#define TIFFClientOpen vtk_TIFFClientOpen
#define TIFFClientdata vtk_TIFFClientdata
#define TIFFClose vtk_TIFFClose
#define TIFFComputeStrip vtk_TIFFComputeStrip
#define TIFFComputeTile vtk_TIFFComputeTile
#define TIFFCreateCustomDirectory vtk_TIFFCreateCustomDirectory
#define TIFFCreateDirectory vtk_TIFFCreateDirectory
#define TIFFCreateEXIFDirectory vtk_TIFFCreateEXIFDirectory
#define TIFFCurrentDirOffset vtk_TIFFCurrentDirOffset
#define TIFFCurrentDirectory vtk_TIFFCurrentDirectory
#define TIFFCurrentRow vtk_TIFFCurrentRow
#define TIFFCurrentStrip vtk_TIFFCurrentStrip
#define TIFFCurrentTile vtk_TIFFCurrentTile
#define TIFFDataWidth vtk_TIFFDataWidth
#define TIFFDefaultDirectory vtk_TIFFDefaultDirectory
#define TIFFDefaultStripSize vtk_TIFFDefaultStripSize
#define TIFFDefaultTileSize vtk_TIFFDefaultTileSize
#define TIFFError vtk_TIFFError
#define TIFFErrorExt vtk_TIFFErrorExt
#define TIFFFaxBlackCodes vtk_TIFFFaxBlackCodes
#define TIFFFaxBlackTable vtk_TIFFFaxBlackTable
#define TIFFFaxMainTable vtk_TIFFFaxMainTable
#define TIFFFaxWhiteCodes vtk_TIFFFaxWhiteCodes
#define TIFFFaxWhiteTable vtk_TIFFFaxWhiteTable
#define TIFFFdOpen vtk_TIFFFdOpen
#define TIFFFieldDataType vtk_TIFFFieldDataType
#define TIFFFieldName vtk_TIFFFieldName
#define TIFFFieldPassCount vtk_TIFFFieldPassCount
#define TIFFFieldReadCount vtk_TIFFFieldReadCount
#define TIFFFieldTag vtk_TIFFFieldTag
#define TIFFFieldWithName vtk_TIFFFieldWithName
#define TIFFFieldWithTag vtk_TIFFFieldWithTag
#define TIFFFieldWriteCount vtk_TIFFFieldWriteCount
#define TIFFFileName vtk_TIFFFileName
#define TIFFFileno vtk_TIFFFileno
#define TIFFFillStrip vtk_TIFFFillStrip
#define TIFFFillTile vtk_TIFFFillTile
#define TIFFFindCODEC vtk_TIFFFindCODEC
#define TIFFFindField vtk_TIFFFindField
#define TIFFFlush vtk_TIFFFlush
#define TIFFFlushData vtk_TIFFFlushData
#define TIFFFlushData1 vtk_TIFFFlushData1
#define TIFFFreeDirectory vtk_TIFFFreeDirectory
#define TIFFGetBitRevTable vtk_TIFFGetBitRevTable
#define TIFFGetClientInfo vtk_TIFFGetClientInfo
#define TIFFGetCloseProc vtk_TIFFGetCloseProc
#define TIFFGetConfiguredCODECs vtk_TIFFGetConfiguredCODECs
#define TIFFGetField vtk_TIFFGetField
#define TIFFGetFieldDefaulted vtk_TIFFGetFieldDefaulted
#define TIFFGetMapFileProc vtk_TIFFGetMapFileProc
#define TIFFGetMode vtk_TIFFGetMode
#define TIFFGetReadProc vtk_TIFFGetReadProc
#define TIFFGetSeekProc vtk_TIFFGetSeekProc
#define TIFFGetSizeProc vtk_TIFFGetSizeProc
#define TIFFGetTagListCount vtk_TIFFGetTagListCount
#define TIFFGetTagListEntry vtk_TIFFGetTagListEntry
#define TIFFGetUnmapFileProc vtk_TIFFGetUnmapFileProc
#define TIFFGetVersion vtk_TIFFGetVersion
#define TIFFGetWriteProc vtk_TIFFGetWriteProc
#define TIFFInitDumpMode vtk_TIFFInitDumpMode
#define TIFFIsBigEndian vtk_TIFFIsBigEndian
#define TIFFIsByteSwapped vtk_TIFFIsByteSwapped
#define TIFFIsCODECConfigured vtk_TIFFIsCODECConfigured
#define TIFFIsMSB2LSB vtk_TIFFIsMSB2LSB
#define TIFFIsTiled vtk_TIFFIsTiled
#define TIFFIsUpSampled vtk_TIFFIsUpSampled
#define TIFFLastDirectory vtk_TIFFLastDirectory
#define TIFFMergeFieldInfo vtk_TIFFMergeFieldInfo
#define TIFFNumberOfDirectories vtk_TIFFNumberOfDirectories
#define TIFFNumberOfStrips vtk_TIFFNumberOfStrips
#define TIFFNumberOfTiles vtk_TIFFNumberOfTiles
#define TIFFOpen vtk_TIFFOpen
#define TIFFPredictorCleanup vtk_TIFFPredictorCleanup
#define TIFFPredictorInit vtk_TIFFPredictorInit
#define TIFFPrintDirectory vtk_TIFFPrintDirectory
#define TIFFRGBAImageBegin vtk_TIFFRGBAImageBegin
#define TIFFRGBAImageEnd vtk_TIFFRGBAImageEnd
#define TIFFRGBAImageGet vtk_TIFFRGBAImageGet
#define TIFFRGBAImageOK vtk_TIFFRGBAImageOK
#define TIFFRasterScanlineSize vtk_TIFFRasterScanlineSize
#define TIFFRasterScanlineSize64 vtk_TIFFRasterScanlineSize64
#define TIFFRawStripSize vtk_TIFFRawStripSize
#define TIFFRawStripSize64 vtk_TIFFRawStripSize64
#define TIFFReadBufferSetup vtk_TIFFReadBufferSetup
#define TIFFReadCustomDirectory vtk_TIFFReadCustomDirectory
#define TIFFReadDirectory vtk_TIFFReadDirectory
#define TIFFReadEXIFDirectory vtk_TIFFReadEXIFDirectory
#define TIFFReadEncodedStrip vtk_TIFFReadEncodedStrip
#define TIFFReadEncodedTile vtk_TIFFReadEncodedTile
#define TIFFReadRGBAImage vtk_TIFFReadRGBAImage
#define TIFFReadRGBAImageOriented vtk_TIFFReadRGBAImageOriented
#define TIFFReadRGBAStrip vtk_TIFFReadRGBAStrip
#define TIFFReadRGBATile vtk_TIFFReadRGBATile
#define TIFFReadRawStrip vtk_TIFFReadRawStrip
#define TIFFReadRawTile vtk_TIFFReadRawTile
#define TIFFReadScanline vtk_TIFFReadScanline
#define TIFFReadTile vtk_TIFFReadTile
#define TIFFRegisterCODEC vtk_TIFFRegisterCODEC
#define TIFFReverseBits vtk_TIFFReverseBits
#define TIFFRewriteDirectory vtk_TIFFRewriteDirectory
#define TIFFScanlineSize vtk_TIFFScanlineSize
#define TIFFScanlineSize64 vtk_TIFFScanlineSize64
#define TIFFSetClientInfo vtk_TIFFSetClientInfo
#define TIFFSetClientdata vtk_TIFFSetClientdata
#define TIFFSetCompressionScheme vtk_TIFFSetCompressionScheme
#define TIFFSetDirectory vtk_TIFFSetDirectory
#define TIFFSetErrorHandler vtk_TIFFSetErrorHandler
#define TIFFSetErrorHandlerExt vtk_TIFFSetErrorHandlerExt
#define TIFFSetField vtk_TIFFSetField
#define TIFFSetFileName vtk_TIFFSetFileName
#define TIFFSetFileno vtk_TIFFSetFileno
#define TIFFSetMode vtk_TIFFSetMode
#define TIFFSetSubDirectory vtk_TIFFSetSubDirectory
#define TIFFSetTagExtender vtk_TIFFSetTagExtender
#define TIFFSetWarningHandler vtk_TIFFSetWarningHandler
#define TIFFSetWarningHandlerExt vtk_TIFFSetWarningHandlerExt
#define TIFFSetWriteOffset vtk_TIFFSetWriteOffset
#define TIFFSetupStrips vtk_TIFFSetupStrips
#define TIFFStripSize vtk_TIFFStripSize
#define TIFFStripSize64 vtk_TIFFStripSize64
#define TIFFSwabArrayOfDouble vtk_TIFFSwabArrayOfDouble
#define TIFFSwabArrayOfFloat vtk_TIFFSwabArrayOfFloat
#define TIFFSwabArrayOfLong vtk_TIFFSwabArrayOfLong
#define TIFFSwabArrayOfLong8 vtk_TIFFSwabArrayOfLong8
#define TIFFSwabArrayOfShort vtk_TIFFSwabArrayOfShort
#define TIFFSwabArrayOfTriples vtk_TIFFSwabArrayOfTriples
#define TIFFSwabDouble vtk_TIFFSwabDouble
#define TIFFSwabFloat vtk_TIFFSwabFloat
#define TIFFSwabLong vtk_TIFFSwabLong
#define TIFFSwabLong8 vtk_TIFFSwabLong8
#define TIFFSwabShort vtk_TIFFSwabShort
#define TIFFTileRowSize vtk_TIFFTileRowSize
#define TIFFTileRowSize64 vtk_TIFFTileRowSize64
#define TIFFTileSize vtk_TIFFTileSize
#define TIFFTileSize64 vtk_TIFFTileSize64
#define TIFFUnRegisterCODEC vtk_TIFFUnRegisterCODEC
#define TIFFUnlinkDirectory vtk_TIFFUnlinkDirectory
#define TIFFUnsetField vtk_TIFFUnsetField
#define TIFFVGetField vtk_TIFFVGetField
#define TIFFVGetFieldDefaulted vtk_TIFFVGetFieldDefaulted
#define TIFFVSetField vtk_TIFFVSetField
#define TIFFVStripSize vtk_TIFFVStripSize
#define TIFFVStripSize64 vtk_TIFFVStripSize64
#define TIFFVTileSize vtk_TIFFVTileSize
#define TIFFVTileSize64 vtk_TIFFVTileSize64
#define TIFFWarning vtk_TIFFWarning
#define TIFFWarningExt vtk_TIFFWarningExt
#define TIFFWriteBufferSetup vtk_TIFFWriteBufferSetup
#define TIFFWriteCheck vtk_TIFFWriteCheck
#define TIFFWriteCustomDirectory vtk_TIFFWriteCustomDirectory
#define TIFFWriteDirectory vtk_TIFFWriteDirectory
#define TIFFWriteEncodedStrip vtk_TIFFWriteEncodedStrip
#define TIFFWriteEncodedTile vtk_TIFFWriteEncodedTile
#define TIFFWriteRawStrip vtk_TIFFWriteRawStrip
#define TIFFWriteRawTile vtk_TIFFWriteRawTile
#define TIFFWriteScanline vtk_TIFFWriteScanline
#define TIFFWriteTile vtk_TIFFWriteTile
#define TIFFXYZToRGB vtk_TIFFXYZToRGB
#define TIFFYCbCrToRGBInit vtk_TIFFYCbCrToRGBInit
#define TIFFYCbCrtoRGB vtk_TIFFYCbCrtoRGB
#define XYZtoRGB24 vtk_XYZtoRGB24
#define _TIFFBuiltinCODECS vtk__TIFFBuiltinCODECS
#define _TIFFCheckMalloc vtk__TIFFCheckMalloc
#define _TIFFCheckRealloc vtk__TIFFCheckRealloc
#define _TIFFCreateAnonField vtk__TIFFCreateAnonField
#define _TIFFDataSize vtk__TIFFDataSize
#define _TIFFDefaultStripSize vtk__TIFFDefaultStripSize
#define _TIFFDefaultTileSize vtk__TIFFDefaultTileSize
#define _TIFFFax3fillruns vtk__TIFFFax3fillruns
#define _TIFFFillStriles vtk__TIFFFillStriles
#define _TIFFFindFieldByName vtk__TIFFFindFieldByName
#define _TIFFFindOrRegisterField vtk__TIFFFindOrRegisterField
#define _TIFFGetExifFields vtk__TIFFGetExifFields
#define _TIFFGetFields vtk__TIFFGetFields
#define _TIFFMergeFields vtk__TIFFMergeFields
#define _TIFFMultiply32 vtk__TIFFMultiply32
#define _TIFFMultiply64 vtk__TIFFMultiply64
#define _TIFFNoFixupTags vtk__TIFFNoFixupTags
#define _TIFFNoPostDecode vtk__TIFFNoPostDecode
#define _TIFFNoPreCode vtk__TIFFNoPreCode
#define _TIFFNoRowDecode vtk__TIFFNoRowDecode
#define _TIFFNoRowEncode vtk__TIFFNoRowEncode
#define _TIFFNoSeek vtk__TIFFNoSeek
#define _TIFFNoStripDecode vtk__TIFFNoStripDecode
#define _TIFFNoStripEncode vtk__TIFFNoStripEncode
#define _TIFFNoTileDecode vtk__TIFFNoTileDecode
#define _TIFFNoTileEncode vtk__TIFFNoTileEncode
#define _TIFFPrintFieldInfo vtk__TIFFPrintFieldInfo
#define _TIFFRewriteField vtk__TIFFRewriteField
#define _TIFFSetDefaultCompressionState vtk__TIFFSetDefaultCompressionState
#define _TIFFSetupFields vtk__TIFFSetupFields
#define _TIFFSwab16BitData vtk__TIFFSwab16BitData
#define _TIFFSwab24BitData vtk__TIFFSwab24BitData
#define _TIFFSwab32BitData vtk__TIFFSwab32BitData
#define _TIFFSwab64BitData vtk__TIFFSwab64BitData
#define _TIFFUInt64ToDouble vtk__TIFFUInt64ToDouble
#define _TIFFUInt64ToFloat vtk__TIFFUInt64ToFloat
#define _TIFFerrorHandler vtk__TIFFerrorHandler
#define _TIFFerrorHandlerExt vtk__TIFFerrorHandlerExt
#define _TIFFfree vtk__TIFFfree
#define _TIFFgetMode vtk__TIFFgetMode
#define _TIFFmalloc vtk__TIFFmalloc
#define _TIFFmemcmp vtk__TIFFmemcmp
#define _TIFFmemcpy vtk__TIFFmemcpy
#define _TIFFmemset vtk__TIFFmemset
#define _TIFFprintAscii vtk__TIFFprintAscii
#define _TIFFprintAsciiTag vtk__TIFFprintAsciiTag
#define _TIFFrealloc vtk__TIFFrealloc
#define _TIFFsetByteArray vtk__TIFFsetByteArray
#define _TIFFsetDoubleArray vtk__TIFFsetDoubleArray
#define _TIFFsetFloatArray vtk__TIFFsetFloatArray
#define _TIFFsetLong8Array vtk__TIFFsetLong8Array
#define _TIFFsetLongArray vtk__TIFFsetLongArray
#define _TIFFsetNString vtk__TIFFsetNString
#define _TIFFsetShortArray vtk__TIFFsetShortArray
#define _TIFFsetString vtk__TIFFsetString
#define _TIFFwarningHandler vtk__TIFFwarningHandler
#define _TIFFwarningHandlerExt vtk__TIFFwarningHandlerExt
#define uv_decode vtk_uv_decode
#define uv_encode vtk_uv_encode

#endif
