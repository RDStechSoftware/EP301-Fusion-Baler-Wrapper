

extern const unsigned char f0001[19];
extern const unsigned char f0002[17];
extern const unsigned char f0003[17];
extern const unsigned char f0004[11];

extern const unsigned char f0005[8];
extern const unsigned char f0006[8];

extern const unsigned char f0008[15];

extern const unsigned char f0011[6];
extern const unsigned char f0012[8];
extern const unsigned char f0013[6];
extern const unsigned char f0014[8];
extern const unsigned char f0015[20];

struct SeqType {
  unsigned char Seq;
  const struct pr *Name;
  };
extern const struct SeqType OPTi[MAXTYPE];

extern const unsigned char *const ErrS[11];

extern const struct pr s0225;
extern const struct pr s0228;

extern const struct pr *const SpeedWarning[3];
extern const struct pr *const ShortLong[3];
extern const struct pr *const OnOff[2];
extern const struct pr *const CropTypeString[3];
extern const struct pr *const KnivSystemString[5];

extern const struct pr *const CropTypeBitmap[3];


