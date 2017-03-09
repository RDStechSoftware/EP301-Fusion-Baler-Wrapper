/* function prototypes */


/* epl_hdw */
extern unsigned char iic_start( void );
extern void iic_clock_start( void );
extern unsigned char iic_transmit( unsigned char data );
extern unsigned char iic_receive( unsigned char ack );
extern void iic_stop( void );
extern void WakeUpDtoA( void );
extern void SetContrast( void );
extern void SetBrightness( void );
extern char btobcd ( char data );
extern char bcdtob ( char data );
extern void get_time( void );
extern void set_time( void );
/* extern void KeyCheck ( void ); */
extern void KeyCheck (unsigned char mode );
extern void LedDisplay( unsigned short int dat );
extern void SetVolume( unsigned char vol );

/* epl_232 */
extern void SetSerial0_Boot( void );
extern void SetSerial0_Normal( void );
extern void CheckSerial0( void );
extern void SetSerial1_Boot( void );
extern void OutSerial0( char *dat );
extern void OutSerial1( char *dat );

/* epl_000 */
extern void reset_factors ( void );
extern void main( void );

/* epl_001 */
extern unsigned char display_f1_number( float data, float offset, float con,
      unsigned char pt, unsigned char co, unsigned char ro, unsigned char just, 
      unsigned char width );
extern unsigned char display_f1_text( const unsigned char *data, unsigned char max,
      unsigned char co, unsigned char ro, unsigned char prog );
extern unsigned char display_f2_number( float data, float offset, float con,
      unsigned char pt, unsigned char co, unsigned char ro, unsigned char just, 
      unsigned char width );
extern unsigned char display_f3_number( float data, float offset, float con,
      unsigned char pt, unsigned char co, unsigned char ro, unsigned char just, 
      unsigned char width );
extern void startup_frame( void );
extern void TimeDisplay( void );

extern void Demo00( void ); /* Demo Screen */
extern void screen00( void ); /* Startup Screen */
extern void screen02( void ); /* Machine Menu Display */
extern void screen03( void ); /* Pin Entry Display */
extern void screen14( void ); /* Operator Menu Display */
extern void screen04( void ); /* Technician Menu Display */
extern void screen07( void ); /* Technician Menu Display */
extern void screen06( void ); /* Reset Defaults */
extern void screen071( void ); /* Diagnostics - Digital inputs */
extern void screen072( void ); /* Diagnostics - Analogue inputs */
extern void screen073( void ); /* Diagnostics - Outputs */
extern void screen074( void ); /* Diagnostics - Remote Test */
extern void screen075( void ); /* Diagnostics - Serial Logging */
extern void screen076( void ); /* Diagnostics - No PWM */
extern void screen11( void ); /* Bale Count */
extern void screen13( void ); /* machine setup 1*/
extern void screen131( void ); /* machine setup 2 */
extern void set_language( void ); /* language setup */
extern void KnifeSystem( void ); /* Knife System */
extern void GrandTotalPin( void );
extern void EditGrandTotBale( void );

extern void SetCropTypeValues( void );
extern void standard_pointer( unsigned char l, unsigned char s, unsigned char i );
extern void standard_pointer1( unsigned char l, unsigned char s, unsigned char i );

/* epl_002 */
extern void command_write( unsigned char data );
extern void write_char( unsigned char data );
extern void write_int( unsigned short int data );
extern void setup_display( void );
extern void display_screen( void );
extern void auto_write( unsigned char data );
extern void auto_reset( void );
extern unsigned char greatest( unsigned char *a, unsigned char *b );
extern void draw_line( unsigned char *buff, unsigned char x1, unsigned char y1,
  unsigned char x2, unsigned char y2, unsigned char method );
extern void draw_box( unsigned char *buff, unsigned char x1, unsigned char y1,
  unsigned char x2, unsigned char y2, unsigned char method );
extern unsigned char write_bitmap( unsigned char *buff, const unsigned char *map,
  unsigned char xpos, unsigned char ypos, unsigned char method );

/* epl_003 */
extern char cf2 ( char c );
extern char cf3 ( char c );

/* epl_004 */
extern void boot_loader( void ); /* bootloader */

/* epl_005 */
extern void display_levels( void ); /* contrast/brightness display */
extern void clock_set( void ); /* time set */
extern void speaker_test( void ); /* speaker test */
extern void screen15(void); /* Baler Full / Net */
extern void screen16(void); /* Bale transfer */
extern void screen17(void); /* Wrapping */
extern void screen18(void); /* Top-Up / Floor */
extern void screen19(void); /* Rotation */
extern void screen20(void); /* Lube Setup */


/* epl_010 */
extern void display_dat( unsigned char pos, unsigned char *pt );
extern void main_loop( void );
extern unsigned char KeyToggle( void );
extern void AutoSequence ( void );
extern void OutputSet( void );
extern void CheckIndexing(void);
extern void Knife_pos_Warn (void);
extern void knife_pos_input_6(void);
extern void knife_pos_input_7(void);

/* epl_011 */
extern void SetLookUps( void );
extern void ResetLubeCheck( void );
extern void ResetType( unsigned short int type );
extern void ResetSequenceFactors( unsigned int seq );
extern void StartWrapSequence( unsigned char mode );
extern unsigned long int ValueToDigit( unsigned short int val );
extern unsigned short int DigitToValue( unsigned long int val );
extern unsigned short int IncCount( unsigned short int val, unsigned char digit, unsigned short int min, unsigned short int max );
extern unsigned short int DecCount( unsigned short int val, unsigned char digit, unsigned short int min, unsigned short int max );
extern void SetOneDispRevs( void );
extern void FilmBreakCheck( void );
extern void SetFilmBreak( void );
extern void SetOneDispenser( void );
extern void CancelBothIfOneDone( struct Sequence *SQSP, unsigned char SeqPnt );
extern unsigned char CheckSwitch( struct Sequence *SQSP, unsigned char SeqPnt );
extern void CheckDelayOrPulse ( struct Sequence *SQSP, unsigned char SeqPnt, unsigned char Action );
extern void LoadDelayAndOutputs ( struct Sequence *SQSP, unsigned char SeqPnt );
extern unsigned char WaitUntilDone ( struct Sequence *SQSP, unsigned char SeqPnt );
extern void SetForResume( void );
extern void SetForReStart( void );
extern void SetBeepType( unsigned char type, unsigned char tone, unsigned char count );
extern void StartUnBlock( void );
extern void UnBlock( void );
extern void StopUnBlock( void );
extern void ResetFloor( void );
extern void SetLedData( void );
extern unsigned char StartDelayComplete( void );
extern void StartTransfer( void );
extern void CheckLubeTopUp( void );
extern void SendDebugString( unsigned char *pt );
extern void CalculateFreq (void);
extern void MonitorKnives( void );


