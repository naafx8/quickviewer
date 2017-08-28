// ZipAddCommon.h

#ifndef __ZIP_ADD_COMMON_H
#define __ZIP_ADD_COMMON_H

#include "../../ICoder.h"
#include "../../IProgress.h"

#include "../../Common/CreateCoder.h"
#include "../../Common/FilterCoder.h"

#include "../../Compress/CopyCoder.h"

#include "../../Crypto/ZipCrypto.h"
#include "../../Crypto/WzAes.h"

#include "ZipCompressionMode.h"

namespace NArchive {
namespace NZip {

struct CCompressingResult
{
  UInt64 UnpackSize;
  UInt64 PackSize;
  UInt32 CRC;
  UInt16 Method;
  Byte ExtractVersion;
  bool FileTimeWasUsed;
  bool LzmaEos;
};

class CAddCommon
{
  CCompressionMethodMode _options;
  NCompress::CCopyCoder *_copyCoderSpec;
  CMyComPtr<ICompressCoder> _copyCoder;

  CMyComPtr<ICompressCoder> _compressEncoder;
  Byte _compressExtractVersion;
  bool _isLzmaEos;

  CFilterCoder *_cryptoStreamSpec;
  CMyComPtr<ISequentialOutStream> _cryptoStream;

  NCrypto::NZip::CEncoder *_filterSpec;
  NCrypto::NWzAes::CEncoder *_filterAesSpec;

  Byte *_buf;
  
  HRESULT CalcStreamCRC(ISequentialInStream *inStream, UInt32 &resultCRC);
public:
  CAddCommon(const CCompressionMethodMode &options);
  ~CAddCommon();

  HRESULT Set_Pre_CompressionResult(bool seqMode, UInt64 unpackSize, CCompressingResult &opRes) const;
  
  HRESULT Compress(
      DECL_EXTERNAL_CODECS_LOC_VARS
      ISequentialInStream *inStream, IOutStream *outStream,
      bool seqMode, UInt32 fileTime,
      ICompressProgressInfo *progress, CCompressingResult &opRes);
};

}}

#endif
