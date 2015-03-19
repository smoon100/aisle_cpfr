/** @defgroup G_LINEA Linea SDK
 Provides access to Linea device series.
 In order to use Linea in your program, several steps have to be performed:
 - Include LineaSDK.h and libdtdev.a in your project.
 - Go to Frameworks and add ExternalAccessory framework
 - Edit your program plist file, add new element and select "Supported external accessory protocols" from the list, then add two items to it -
 com.datecs.linea.pro.msr and com.datecs.linea.pro.bar
 @{
 */

#define LINEA_NO_EXCEPTIONS

//backward compatibility defines
#define buttonPressed lineaButtonPressed
#define buttonReleased lineaButtonReleased
#define btmSetEnabled btSetEnabled

#define btmGetEnabled btGetEnabled
#define btmWrite btWrite
#define btmRead btRead
#define btmReadLine btReadLine
#define btmGetLocalName btGetLocalName
#define prnDiscoverPrinters btDiscoverPrinters
#define prnDiscoverPrintersInBackground btDiscoverPrintersInBackground

#define barcodeEngineSetInitString barcodeOpticonSetInitString

#define msStartScan msEnable
#define msStopScan msDisable
#define setMSCardDataMode msSetCardDataMode
#define getMSCardDataMode msGetCardDataMode
#define startScan barcodeStartScan
#define stopScan barcodeStopScan
#define getScanTimeout barcodeGetScanTimeout
#define setScanTimeout barcodeSetScanTimeout
#define getScanButtonMode barcodeGetScanButtonMode
#define setScanButtonMode barcodeSetScanButtonMode
#define setScanBeep barcodeSetScanBeep
#define getScanMode barcodeGetScanMode
#define setScanMode barcodeSetScanMode
#define enableBarcode barcodeEnableBarcode
#define isBarcodeEnabled barcodeIsBarcodeEnabled
#define isBarcodeSupported barcodeIsBarcodeSupported
#define getBarcodeTypeMode barcodeGetTypeMode
#define setBarcodeTypeMode barcodeSetTypeMode

#define cryptoRawAuthenticateLinea cryptoRawAuthenticateDevice
#define cryptoRawAuthenticateiPod cryptoRawAuthenticateHost
#define cryptoAuthenticateLinea cryptoAuthenticateDevice
#define cryptoAuthenticateiPod cryptoAuthenticateHost

#ifndef __has_feature         // Optional of course.
#define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif

#ifndef STRUCTURES_DEFINED
#define STRUCTURES_DEFINED
typedef enum {
	BAR_ALL=0,
	BAR_UPC,
	BAR_CODABAR,
	BAR_CODE25_NI2OF5,
	BAR_CODE25_I2OF5,
	BAR_CODE39,
	BAR_CODE93,
	BAR_CODE128,
	BAR_CODE11,
	BAR_CPCBINARY,
	BAR_DUN14,
	BAR_EAN2,
	BAR_EAN5,
	BAR_EAN8,
	BAR_EAN13,
	BAR_EAN128,
	BAR_GS1DATABAR,
	BAR_ITF14,
	BAR_LATENT_IMAGE,
	BAR_PHARMACODE,
	BAR_PLANET,
	BAR_POSTNET,
	BAR_INTELLIGENT_MAIL,
	BAR_MSI,
	BAR_POSTBAR,
	BAR_RM4SCC,
	BAR_TELEPEN,
	BAR_PLESSEY,
	BAR_PDF417,
	BAR_MICROPDF417,
	BAR_DATAMATRIX,
	BAR_AZTEK,
	BAR_QRCODE,
	BAR_MAXICODE,
	BAR_LAST
}BARCODES;

typedef enum {
	BAR_EX_ALL=0,
	BAR_EX_UPCA,
	BAR_EX_CODABAR,
	BAR_EX_CODE25_NI2OF5,
	BAR_EX_CODE25_I2OF5,
	BAR_EX_CODE39,
	BAR_EX_CODE93,
	BAR_EX_CODE128,
	BAR_EX_CODE11,
	BAR_EX_CPCBINARY,
	BAR_EX_DUN14,
	BAR_EX_EAN2,
	BAR_EX_EAN5,
	BAR_EX_EAN8,
	BAR_EX_EAN13,
	BAR_EX_EAN128,
	BAR_EX_GS1DATABAR,
	BAR_EX_ITF14,
	BAR_EX_LATENT_IMAGE,
	BAR_EX_PHARMACODE,
	BAR_EX_PLANET,
	BAR_EX_POSTNET,
	BAR_EX_INTELLIGENT_MAIL,
	BAR_EX_MSI_PLESSEY,
	BAR_EX_POSTBAR,
	BAR_EX_RM4SCC,
	BAR_EX_TELEPEN,
	BAR_EX_UK_PLESSEY,
	BAR_EX_PDF417,
	BAR_EX_MICROPDF417,
	BAR_EX_DATAMATRIX,
	BAR_EX_AZTEK,
	BAR_EX_QRCODE,
	BAR_EX_MAXICODE,
	BAR_EX_RESERVED1,
	BAR_EX_RESERVED2,
	BAR_EX_RESERVED3,
	BAR_EX_RESERVED4,
	BAR_EX_RESERVED5,
	BAR_EX_UPCA_2,
	BAR_EX_UPCA_5,
	BAR_EX_UPCE,
	BAR_EX_UPCE_2,
	BAR_EX_UPCE_5,
	BAR_EX_EAN13_2,
	BAR_EX_EAN13_5,
	BAR_EX_EAN8_2,
	BAR_EX_EAN8_5,
	BAR_EX_CODE39_FULL,
	BAR_EX_ITA_PHARMA,
	BAR_EX_CODABAR_ABC,
	BAR_EX_CODABAR_CX,
	BAR_EX_SCODE,
	BAR_EX_MATRIX_2OF5,
	BAR_EX_IATA,
	BAR_EX_KOREAN_POSTAL,
	BAR_EX_CCA,
	BAR_EX_CCB,
	BAR_EX_CCC,
	BAR_EX_LAST
}BARCODES_EX;

/**
 * Connection state
 */
typedef enum {
    /**
     Device is disconnected, no automatic connection attempts will be made
     */
	CONN_DISCONNECTED=0,
    /**
     The SDK is trying to connect to the device
     */
	CONN_CONNECTING,
    /**
     Device is connected
     */
	CONN_CONNECTED
}CONN_STATES;

/**
 Filtering bluetooth devices to discover
 */
typedef enum {
    /**
     Include all supported devices (default)
     */
	BLUETOOTH_FILTER_ALL=-1,
    /**
     Include supported printers
     */
	BLUETOOTH_FILTER_PRINTERS=1,
    /**
     Include supported pinpads
     */
	BLUETOOTH_FILTER_PINPADS=2,
    /**
     Include supported barcode scanners
     */
	BLUETOOTH_FILTER_BARCODE_SCANNERS=4,
}BLUETOOTH_FILTER;

/**
 Barcode scan modes
 */
typedef enum {
    /**
     The scan will be terminated after successful barcode recognition (default)
     */
	MODE_SINGLE_SCAN=0,
    /**
     Scanning will continue unless either scan button is releasd, or stop scan function is called
     */
	MODE_MULTI_SCAN,
    /**
     For as long as scan button is pressed or stop scan is not called the engine will operate in low power scan mode trying to detect objects entering the area, then will turn on the lights and try to read the barcode. Supported only on Code engine.
     */
	MODE_MOTION_DETECT,
    /**
     Pressing the button/start scan will enter aim mode, while a barcode scan will actually be performed upon button release/stop scan.
     */
	MODE_SINGLE_SCAN_RELEASE,
    /**
     Same as multi scan mode, but allowing no duplicate barcodes to be scanned
     */
	MODE_MULTI_SCAN_NO_DUPLICATES,
}SCAN_MODES;

/**
 Button modes
 */
typedef enum {
    /**
     Button is disabled
     */
	BUTTON_DISABLED=0,
    /**
     Button is enabled (default)
     */
	BUTTON_ENABLED
}BUTTON_STATES;

/**
 Card data mode
 */
typedef enum {
    /**
     Card data is processed and tracks are extracted (default)
     */
	MS_PROCESSED_CARD_DATA=0,
    /**
     Card data will be returned as RAW sequence of bits
     */
	MS_RAW_CARD_DATA
}MS_MODES;

/**
 The way to return barcode types
 */
typedef enum {
    /**
     Barcode types are returned from the BAR_* list (default)
     */
	BARCODE_TYPE_DEFAULT=0,
    /**
     Barcode types are returned from the extended barcode list - BAR_EX_*
     */
	BARCODE_TYPE_EXTENDED,
    /**
     Barcode types are returned as ISO 15424 format
     */
    BARCODE_TYPE_ISO15424
}BT_MODES;

/**
 Firmware update phases
 */
typedef enum {
    /**
     Initializing update
     */
	UPDATE_INIT=0,
    /**
     Erasing old firmware/preparing memory
     */
	UPDATE_ERASE,
    /**
     Writing data
     */
    UPDATE_WRITE,
    /**
     Update complete, this is the final phase
     */
    UPDATE_FINISH,
    /**
     Post-update operations
     */
    UPDATE_COMPLETING
}UPDATE_PHASES;

/**
 AES 256 encryption algorithm
 */
#define ALG_AES256		0
/**
 Encrypted Head ECC encryption algorithm
 */
#define ALG_EH_ECC      1
/**
 Encrypted Head AES 256 encryption algorithm
 */
#define ALG_EH_AES256   2
/**
 Encrypted Head IDTECH encryption algorithm
 */
#define ALG_EH_IDTECH   3
/**
 Encrypted Head MAGTEK encryption algorithm
 */
#define ALG_EH_MAGTEK   4
/**
 Encrypted Head 3DES encryption algorithm
 */
#define ALG_EH_3DES   5
/**
 Encrypted Head RSA encryption algorithm
 */
#define ALG_EH_RSA_OAEP   6

/**
 Authentication key
 */
#define KEY_AUTHENTICATION 0x00
/**
 Encryption key, if set magnetic card data will be encrypted
 */
#define KEY_ENCRYPTION 0x01
/**
 Encrypted head key loading key
 */
#define KEY_EH_AES256_LOADING 0x02
/**
 Encrypted head TMK key
 */
#define KEY_EH_TMK_AES 0x10
/**
 Encrypted head DUKPT master key
 */
#define KEY_EH_DUKPT_MASTER 0x20

/**
 This flag locks barcode, magnetic card and bluetooth usage, so it will be possible to use them only after authenticating
 */
#define KEY_AUTH_FLAG_LOCK 1


/**
 In the case where the AES256 key can be disabled to return the devce to plain text (LP without encrypted head), loading this key will remove it
 */
extern const uint8_t KEY_AES256_EMPTY[32];

/**
 RF card types
 */
typedef enum
{
    /**
     Unknown card
     */
	CARD_UNKNOWN=0,
    /**
     Mifare Mini
     */
	CARD_MIFARE_MINI,
    /**
     Mifare Classic 1K
     */
	CARD_MIFARE_CLASSIC_1K,
    /**
     Mifare Classic 4K
     */
	CARD_MIFARE_CLASSIC_4K,
    /**
     Mifare Ultralight
     */
	CARD_MIFARE_ULTRALIGHT,
    /**
     Mifare Ultralight C
     */
	CARD_MIFARE_ULTRALIGHT_C,
    /**
     ISO 14443A
     */
	CARD_ISO14443A,
    /**
     Mifare Plus
     */
	CARD_MIFARE_PLUS,
    /**
     ISO 15693
     */
	CARD_ISO15693,
    /**
     Mifare Desfire
     */
	CARD_MIFARE_DESFIRE,
    /**
     ISO 14443B
     */
	CARD_ISO14443B,
    /**
     FeliCa
     */
	CARD_FELICA,
}RF_CARD_TYPES;

/**
 FeliCa SmartTag battery status
 */
typedef enum
{
    /**
     Normal, card can be used
     */
	FELICA_SMARTTAG_BATTERY_NORMAL1=0,
    /**
     Normal, card can be used
     */
	FELICA_SMARTTAG_BATTERY_NORMAL2,
    /**
     Low, consider replacing
     */
    FELICA_SMARTTAG_BATTERY_LOW1,
    /**
     Very Low, replace it
     */
    FELICA_SMARTTAG_BATTERY_LOW2,
}FELICA_SMARTTAG_BATERY_STATUSES;

/**
 Device name as string, for example "Linea"
 */
extern NSString * const InfoDeviceName;
/**
 Device model, if any, for example "XAMBL"
 */
extern NSString * const InfoDeviceModel;
/**
 Firmware revision as string, for example 2.41
 */
extern NSString * const InfoFirmwareRevision;
/**
 Firmware revision as number, useful for comparison, for example 241
 */
extern NSString * const InfoFirmwareRevisionNumber;

/**
 Information about RF card
 */
@interface DTRFCardInfo : NSObject
/**
 RF card type, one of the CARD_* constants
 */
@property (assign) int type;
/**
 RF card type as string, useful for display purposes
 */
@property (assign) NSString *typeStr;
/**
 RF card unique identifier, if any
 */
@property (assign) NSData *UID;
/**
 Mifare card ATQA
 */
@property (assign) int ATQA;
/**
 Mifare card SAK
 */
@property (assign) int SAK;
/**
 ISO15693 card AFI
 */
@property (assign) int AFI;
/**
 ISO15693 card DSFID
 */
@property (assign) int DSFID;
/**
 ISO15693 card block size
 */
@property (assign) int blockSize;
/**
 ISO15693 card number of blocks
 */
@property (assign) int nBlocks;
@end
#endif



/**
 Protocol describing various notifications that LineaSDK can send.
 @ingroup G_LINEA
 */
@protocol LineaDelegate
@optional
/** @defgroup G_LNDELEGATE Delegate Notifications
 @ingroup G_LINEA
 Notifications sent by the sdk on various events - barcode scanned, magnetic card data, communication status, etc
 @{
 */

/**
 Notifies about the current connection state
 @param state - connection state, one of:
 <table>
 <tr><td>CONN_DISCONNECTED</td><td>there is no connection to Linea and the sdk will not try to make one even if the device is attached</td></tr>
 <tr><td>CONN_CONNECTING</td><td>Linea is not currently connected, but the sdk is actively trying to</td></tr>
 <tr><td>CONN_CONNECTED</td><td>Linea is connected</td></tr>
 </table>
 **/
-(void)connectionState:(int)state;

/**
 Notification sent when some of the Linea's buttons is pressed
 @param which button identifier, one of:
 <table>
 <tr><td>0</td><td>right scan button</td></tr>
 </table>
 **/
-(void)buttonPressed:(int)which;

/**
 Notification sent when some of the Linea's buttons is released
 @param which button identifier, one of:
 <table>
 <tr><td>0</td><td>right scan button</td></tr>
 </table>
 **/
-(void)buttonReleased:(int)which;

/**
 Notification sent when barcode is successfuly read. This notification is used when barcode type is set to BARCODE_TYPE_DEFAULT or BARCODE_TYPE_EXTENDED.
 @param barcode - string containing barcode data
 @param type - barcode type, one of the BAR_* constants
 **/
-(void)barcodeData:(NSString *)barcode type:(int)type;

/**
 Notification sent when barcode is successfuly read. This notification is used when barcode type is set to BARCODE_TYPE_ISO15424, or barcode engine is CR-800.
 @param barcode - string containing barcode data
 @param type - barcode type, one of the BAR_* constants
 **/
-(void)barcodeData:(NSString *)barcode isotype:(NSString *)isotype;

/**
 Notification sent when magnetic card is successfuly read
 @param track1 - data contained in track 1 of the magnetic card or nil
 @param track2 - data contained in track 2 of the magnetic card or nil
 @param track3 - data contained in track 3 of the magnetic card or nil
 **/
-(void)magneticCardData:(NSString *)track1 track2:(NSString *)track2 track3:(NSString *)track3;

/**
 Notification sent when magnetic card is successfuly read
 @param tracks contains the raw magnetic card data. These are the bits directly from the magnetic head.
 The maximum length of a single track is 704 bits (88 bytes), so the command returns the 3 tracks as 3x88 bytes block
 **/
-(void)magneticCardRawData:(NSData *)tracks;

/**
 Notification sent when magnetic card is successfuly read. The data is being sent encrypted.
 @param encryption encryption algorithm used, one of:
 <table>
 <tr><td>0</td><td>AES 256</td></tr>
 <tr><td>1</td><td>IDTECH with DUKPT</td></tr>
 </table>
 
 For AES256, after decryption, the result data will be as follows:
 - Random data (4 bytes)
 - Device identification text (16 ASCII characters, unused bytes are 0)
 - Processed track data in the format: 0xF1 (track1 data), 0xF2 (track2 data) 0xF3 (track3 data). It is possible some of the tracks will be empty, then the identifier will not be present too, for example 0xF1 (track1 data) 0xF3 (track3 data)
 - End of track data (byte 0x00)
 - CRC16 (2 bytes) - the CRC is performed from the start of the encrypted block (the Random Data block) to the end of the track data (including the 0x00 byte).
 The data block is rounded to 16 bytes
 
 In the more secure way, where the decryption key resides in a server only, the card read process will look something like:
 - (User) swipes the card
 - (iOS program) receives the data via magneticCardEncryptedData and sends to the server
 - (iOS program)[optional] sends current Linea serial number along with the data received from magneticCardEncryptedData. This can be used for data origin verification
 - (Server) decrypts the data, extracts all the information from the fields
 - (Server)[optional] if the ipod program have sent the Linea serial number before, the server compares the received serial number with the one that's inside the encrypted block
 - (Server) checks if the card data is the correct one, i.e. all needed tracks are present, card is the same type as required, etc and sends back notification to the ipod program.
 
 For IDTECH with DUKPT the data contains:
 - DATA[0]:	CARD TYPE: 0 - payment card
 - DATA[1]:	TRACK FLAGS
 - DATA[2]:	TRACK 1 LENGTH
 - DATA[3]:	TRACK 2 LENGTH
 - DATA[4]:	TRACK 3 LENGTH
 - DATA[??]:	TRACK 1 DATA MASKED
 - DATA[??]:	TRACK 2 DATA MASKED
 - DATA[??]:	TRACK 3 DATA
 - DATA[??]:	TRACK 1 AND TRACK 2 TDES ENCRYPTED
 - DATA[??]:	TRACK 1 SHA1 (0x14 BYTES)
 - DATA[??]:	TRACK 2 SHA1 (0x14 BYTES)
 - DATA[??]:	DUKPT SERIAL AND COUNTER (0x0A BYTES)
 
 @param data contains the encrypted card data
 **/
-(void)magneticCardEncryptedData:(int)encryption data:(NSData *)data;

/**
 Notification sent when magnetic card is successfuly read. The data is being sent encrypted.
 @param encryption encryption algorithm used, one of:
 <table>
 <tr><td>0</td><td>AES 256</td></tr>
 <tr><td>1</td><td>IDTECH with DUKPT</td></tr>
 </table>
 
 For AES256, after decryption, the result data will be as follows:
 - Random data (4 bytes)
 - Device identification text (16 ASCII characters, unused bytes are 0)
 - Processed track data in the format: 0xF1 (track1 data), 0xF2 (track2 data) 0xF3 (track3 data). It is possible some of the tracks will be empty, then the identifier will not be present too, for example 0xF1 (track1 data) 0xF3 (track3 data)
 - End of track data (byte 0x00)
 - CRC16 (2 bytes) - the CRC is performed from the start of the encrypted block (the Random Data block) to the end of the track data (including the 0x00 byte).
 The data block is rounded to 16 bytes
 
 In the more secure way, where the decryption key resides in a server only, the card read process will look something like:
 - (User) swipes the card
 - (iOS program) receives the data via magneticCardEncryptedData and sends to the server
 - (iOS program)[optional] sends current Linea serial number along with the data received from magneticCardEncryptedData. This can be used for data origin verification
 - (Server) decrypts the data, extracts all the information from the fields
 - (Server)[optional] if the ipod program have sent the Linea serial number before, the server compares the received serial number with the one that's inside the encrypted block
 - (Server) checks if the card data is the correct one, i.e. all needed tracks are present, card is the same type as required, etc and sends back notification to the ipod program.
 
 For IDTECH with DUKPT the data contains:
 - DATA[0]:	CARD TYPE: 0 - payment card
 - DATA[1]:	TRACK FLAGS
 - DATA[2]:	TRACK 1 LENGTH
 - DATA[3]:	TRACK 2 LENGTH
 - DATA[4]:	TRACK 3 LENGTH
 - DATA[??]:	TRACK 1 DATA MASKED
 - DATA[??]:	TRACK 2 DATA MASKED
 - DATA[??]:	TRACK 3 DATA
 - DATA[??]:	TRACK 1 AND TRACK 2 TDES ENCRYPTED
 - DATA[??]:	TRACK 1 SHA1 (0x14 BYTES)
 - DATA[??]:	TRACK 2 SHA1 (0x14 BYTES)
 - DATA[??]:	DUKPT SERIAL AND COUNTER (0x0A BYTES)
 
 @param tracks contain information which tracks are successfully read and inside the encrypted data as bit fields, bit 1 corresponds to track 1, etc, so value of 7 means all tracks are read
 @param data contains the encrypted card data
 **/
-(void)magneticCardEncryptedData:(int)encryption tracks:(int)tracks data:(NSData *)data;

/**
 Notification sent when magnetic card is successfuly read. The data is being sent encrypted.
 @param encryption encryption algorithm used, one of:
 <table>
 <tr><td>0</td><td>AES 256</td></tr>
 <tr><td>1</td><td>IDTECH with DUKPT</td></tr>
 </table>
 
 For AES256, after decryption, the result data will be as follows:
 - Random data (4 bytes)
 - Device identification text (16 ASCII characters, unused bytes are 0)
 - Processed track data in the format: 0xF1 (track1 data), 0xF2 (track2 data) 0xF3 (track3 data). It is possible some of the tracks will be empty, then the identifier will not be present too, for example 0xF1 (track1 data) 0xF3 (track3 data)
 - End of track data (byte 0x00)
 - CRC16 (2 bytes) - the CRC is performed from the start of the encrypted block (the Random Data block) to the end of the track data (including the 0x00 byte).
 The data block is rounded to 16 bytes
 
 In the more secure way, where the decryption key resides in a server only, the card read process will look something like:
 - (User) swipes the card
 - (iOS program) receives the data via magneticCardEncryptedData and sends to the server
 - (iOS program)[optional] sends current Linea serial number along with the data received from magneticCardEncryptedData. This can be used for data origin verification
 - (Server) decrypts the data, extracts all the information from the fields
 - (Server)[optional] if the ipod program have sent the Linea serial number before, the server compares the received serial number with the one that's inside the encrypted block
 - (Server) checks if the card data is the correct one, i.e. all needed tracks are present, card is the same type as required, etc and sends back notification to the ipod program.
 
 For IDTECH with DUKPT the data contains:
 - DATA[0]:	CARD TYPE: 0 - payment card
 - DATA[1]:	TRACK FLAGS
 - DATA[2]:	TRACK 1 LENGTH
 - DATA[3]:	TRACK 2 LENGTH
 - DATA[4]:	TRACK 3 LENGTH
 - DATA[??]:	TRACK 1 DATA MASKED
 - DATA[??]:	TRACK 2 DATA MASKED
 - DATA[??]:	TRACK 3 DATA
 - DATA[??]:	TRACK 1 AND TRACK 2 TDES ENCRYPTED
 - DATA[??]:	TRACK 1 SHA1 (0x14 BYTES)
 - DATA[??]:	TRACK 2 SHA1 (0x14 BYTES)
 - DATA[??]:	DUKPT SERIAL AND COUNTER (0x0A BYTES)
 
 @param tracks contain information which tracks are successfully read and inside the encrypted data as bit fields, bit 1 corresponds to track 1, etc, so value of 7 means all tracks are read
 @param data contains the encrypted card data
 @param track1masked when possible, track1 data will be masked and returned here
 @param track2masked when possible, track2 data will be masked and returned here
 **/
-(void)magneticCardEncryptedData:(int)encryption tracks:(int)tracks data:(NSData *)data track1masked:(NSString *)track1masked track2masked:(NSString *)track2masked track3:(NSString *)track3;

/**
 Notification sent when magnetic card is successfuly read. The raw card data is encrypted via the selected encryption algorithm.
 After decryption, the result data will be as follows:
 - Random data (4 bytes)
 - Device identification text (16 ASCII characters, unused bytes are 0)
 - Track data: the maximum length of a single track is 704 bits (88 bytes), so track data contains 3x88 bytes
 - CRC16 (2 bytes) - the CRC is performed from the start of the encrypted block (the Random Data block) to the end of the track data.
 The data block is rounded to 16 bytes
 @param encryption encryption algorithm used, one of:
 <table>
 <tr><td>0</td><td>AES 256</td></tr>
 </table>
 @param data - Contains the encrypted raw card data
 **/
-(void)magneticCardEncryptedRawData:(int)encryption data:(NSData *)data;

/**
 Notification sent when firmware update process advances. Do not call any linea functions until firmware update is complete! During the firmware update notifications will be posted.
 @param phase update phase, one of:
 <table>
 <tr><td>UPDATE_INIT</td><td>Initializing firmware update</td></tr>
 <tr><td>UPDATE_ERASE</td><td>Erasing flash memory</td></tr>
 <tr><td>UPDATE_WRITE</td><td>Writing data</td></tr>
 <tr><td>UPDATE_FINISH</td><td>Update complete</td></tr>
 </table>
 @param percent firmware update progress in percents
 **/
-(void)firmwareUpdateProgress:(int)phase percent:(int)percent;

/**
 Notification sent when bluetooth discovery finds new bluetooth device
 @param success true if the discovery complete successfully, even if it not resulted in any device found, false if there was an error communicating with the bluetooth module
 **/
-(void)bluetoothDiscoverComplete:(BOOL)success;

/**
 Notification sent when bluetooth discovery finds new bluetooth device
 @param btAddress bluetooth address of the device
 @param btName bluetooth name of the device
 **/
-(void)bluetoothDeviceDiscovered:(NSString *)btAddress name:(NSString *)btName;

/**
 Notification sent when JIS I & II magnetic card is successfuly read
 @param data - data contained in the magnetic card
 **/
-(void)magneticJISCardData:(NSString *)data;

/**
 Notification sent when a new supported RFID card enters the field
 @param cardIndex the index of the card, use this index with all subsequent commands to the card
 @param type card type, one of the CARD_* constants
 @param info information about the card
 **/
-(void)rfCardDetected:(int)cardIndex info:(DTRFCardInfo *)info;

/**
 Notification sent when the card leaves the field
 @param cardIndex the index of the card, use this index with all subsequent commands to the card
 */
-(void)rfCardRemoved:(int)cardIndex;

/**@}*/

@end


/**
 Provides access to Linea functions.
 */
@interface Linea : NSObject

/** @defgroup G_LNGENERAL General functions
 @ingroup G_LINEA
 Functions to connect/disconnect, set delegate, make sounds, update firmware, control various device settings
 @{
 */

/**
 Creates and initializes new Linea class instance or returns already initalized one. Use this function, if you want to access the class from different places
 @return shared class instance
 **/
+(id)sharedDevice;

/**
 Allows unlimited delegates to be added to a single class instance. This is useful in the case of global
 class and every view can use addDelegate when the view is shown and removeDelegate when no longer needs to monitor events
 @param newDelegate the delegate that will be notified of Linea events
 **/
-(void)addDelegate:(id)newDelegate;

/**
 Removes delegate, previously added with addDelegate
 @param newDelegate the delegate that will be no longer be notified of Linea events
 **/
-(void)removeDelegate:(id)newDelegate;

/**
 Tries to connect to Linea in the background, connection status notifications will be passed through the delegate.
 Once connect is called, it will automatically try to reconnect until disconnect is called. Note that "connect" call works in background and will notify the caller of connection success via connectionState delegate. Do not assume the library has fully connected to the device after this call, but wait for the notification.
 **/
-(void)connect;

/**
 Stops the sdk from trying to connect to Linea and breaks existing connection.
 **/
-(void)disconnect;

/*
 Checks if accessory is presnet - either already connected, or physically attached, even if not connected to
 @return true if the accessory is either connected or physically attached
 */
-(BOOL)isPresent;

/**
 Returns Linea's battery capacity
 @note Reading battery voltages during charging (both Linea charing and Linea charging the iPod) is unreliable!
 @param capacity returns battery capacity in percents, ranging from 0 when battery is dead to 100 when fully charged. Pass nil if you don't want that information
 @param voltage returns battery voltage in Volts, pass nil if you don't want that information
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)getBatteryCapacity:(int *)capacity voltage:(float *)voltage error:(NSError **)error;

/**
 Makes Linea plays a sound using the built-in speaker
 @note A sample beep containing of 2 tones, each with 400ms duration, first one 2000Hz and second - 5000Hz will look int beepData[]={2000,400,5000,400}
 @param volume controls the volume (0-100). Currently have no effect
 @param data an array of integer values specifying pairs of tone(Hz) and duration(ms).
 @param length length in bytes of beepData array
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)playSound:(int)volume beepData:(int *)data length:(int)length error:(NSError **)error;

/**
 Returns if Linea is charging the iOS device from it's own battery. Linea firmware versions prior to 2.13 will return true if external charge is attached, 2.13 and later will return only if Linea's own battery is used for charging.
 @param charging returns TRUE if charging is enabled (from internal battery, external charging is omitted)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)getCharging:(BOOL *)charging error:(NSError **)error;

/**
 Enables or disables Lines's capability to charge the handheld from it's own battery. Charging can stop if Linea's battery goes too low.
 
 <br>While Linea can act as external battery for the iPod/iPhone, there are certain limitations if you decide to implement it. The internal battery is not big enough, so if the iPod/iPhone consumes a lot of power from it, it will go down very fast and force the firmware to cut the charge to prevent going down to dangerous levels. The proper use of this charging function depends on how the program, running on the iPod/iPhone, is used and how the iPod/iPhone is discharged
 
 <br>There are two possible ways to use Linea's charge:
 - Emergency mode - in the case iPod/iPhone usage is designed in a way it will last long enough between charging sessions and using Linea's charge is not generally needed, the charge can be used if the iPod/iPhone for some reason goes too low (like <50%), so it is given some power to continue working until next charging. An example will be store, where devices are being charged every night, but extreme usage on some iPod drains the battery before the end of the shift.
 This is the less efficient way to charge it, also, Linea will refuse to start the charge if it's own battery goes below 3.8v, so depending on the usage, barcode type and if the barcode engine is set to work all the time, it may not be possible to start the charge.
 
 - Max life mode - it is the case where both devices are required to operate as long as possible. Usually, the iPod/iPhone's battery will be drained way faster than Linea's, especially with wifi enabled programs and to keep both devices operating as long as possible, the charging should be desinged in a way so iPod/iPhone is able to use most of Linea's battery. This is possible, if you start charging when iPod/iPhone is almost full - at around 75-80% or higher. This way the iPod will consume small amount of energy, allowing our battery to slowly be used almost fully to charge it.
 
 <br>LineaDemo application contains sample implementation of max life mode charging.
 
 @note Reading battery voltages during charging is unreliable!
 @note Enabling charge can fail if Linea's battery is low. Disabling charge will fail if there is external charger or usb cable attached.
 
 @param enabled TRUE to enable charging, FALSE to disable/stop it
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)setCharging:(BOOL)enabled error:(NSError **)error;

/**
 Returns information about the specified firmware data. Based on it, and the connected Linea's name, model and firmware version you can chose to update or not the Linea's firmware
 @param data - firmware data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return firmware information if function succeeded, nil otherwise. See Info* constants for possible keys in the returned dictionary.
 **/
-(NSDictionary *)getFirmwareFileInformation:(NSData *)data error:(NSError **)error;

/**
 Updates Linea's firmware with specified firmware data. The firmware can only be upgraded or downgraded, if you send the same firmware version, then no update process will be started.
 @note Make sure the user does not interrupt the process or the device will be rendered unusable and can only be recovered via the special firmware update cable
 @param data the firmware data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)updateFirmwareData:(NSData *)data error:(NSError **)error;

/**
 Returns the current sync button mode. See setSyncButtonMode for more detailed description. This setting is stored into flash memory and will persist.
 @note Although this function was made for Linea 1, that had hardware button to enter sync mode, it still works for enabling/disabling automated sync on Linea 4 and onward
 @param mode returns sync button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's will not perform synchronization when you press and hold the button for 3 seconds</td></tr>
 <tr><td>BUTTON_ENABLED</td><td>Linea's will perform synchronization when you press and hold the button for 3 seconds</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)getSyncButtonMode:(int *)mode error:(NSError **)error;

/**
 Sets Linea's sync button mode. This setting is stored into flash memory and will persist.
 @note Although this function was made for Linea 1, that had hardware button to enter sync mode, it still works for enabling/disabling automated sync on Linea 4 and onward
 @param mode button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's will not perform synchronization when you press and hold the button for 3 seconds</td></tr>
 <tr><td>BUTTON_ENABLED (default)</td><td>Linea's will perform synchronization when you press and hold the button for 3 seconds</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)setSyncButtonMode:(int)mode error:(NSError **)error;

/**@}*/



/** @defgroup G_LNMSREADER Magnetic Stripe Reader Functions
 Functions to work with the Linea's built-in magenetic card reader
 @ingroup G_LINEA
 @{
 */

/**
 Enables reading of magnetic cards. Whenever a card is successfully read, the magneticCardData delegate will be called. Current magnetic card heads used in Linea consume so little power, that there is no drawback in leaving scanning enabled all the time.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)msEnable:(NSError **)error;

/**
 Disables magnetic card scanning started with msEnable
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)msDisable:(NSError **)error;

/**
 Helper function to parse financial card and extract the data - name, number, expiration date. The function will extract as much information as possible.
 @param track1 - track1 information or nil
 @param track2 - track2 information or nil
 @return dictionary containing extracted data or nil if the data is invalid. Keys contained are:
 <table>
 <tr><td>"accountNumber"</td><td>Account number</td></tr>
 <tr><td>"cardholderName"</td><td>Cardholder name, as stored in the card</td></tr>
 <tr><td>"expirationYear"</td><td>Expiration date - year</td></tr>
 <tr><td>"expirationMonth"</td><td>Expiration date - month</td></tr>
 <tr><td>"serviceCode"</td><td>Service code (if any)</td></tr>
 <tr><td>"discretionaryData"</td><td>Discretionary data (if any)</td></tr>
 <tr><td>"firstName"</td><td>Extracted cardholder's first name</td></tr>
 <tr><td>"lastName"</td><td>Extracted cardholder's last name</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 **/
-(NSDictionary *)msProcessFinancialCard:(NSString *)track1 track2:(NSString *)track2;

/**
 Returns the current magnetic card data mode.
 This setting is not persistent and is best to configure it upon connect.
 @return card data mode, one of the:
 <table>
 <tr><td>MS_PROCESSED_CARD_DATA</td><td>Card data will be processed and will be returned via call to magneticCardData</td></tr>
 <tr><td>MS_RAW_CARD_DATA</td><td>Card data will not be processed and will be returned via call to magneticCardRawData</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)msGetCardDataMode:(int *)mode error:(NSError **)error;

/**
 Sets Linea's magnetic card data mode. This setting is not persistent and is best to configure it upon connect.
 @param mode magnetic card data mode:
 <table>
 <tr><td>MS_PROCESSED_CARD_DATA</td><td>Card data will be processed and will be returned via call to magneticCardData</td></tr>
 <tr><td>MS_RAW_CARD_DATA</td><td>Card data will not be processed and will be returned via call to magneticCardRawData</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)msSetCardDataMode:(int)mode error:(NSError **)error;
/**@}*/



/** @defgroup G_LNBARCODEREADER Barcode Reader Functions
 Functions for scanning barcodes, various barcode settings and direct control of the barcode engine
 @ingroup G_LINEA
 @{
 */

/**
 Helper function to return string name of barcode type
 @param barcodeType barcode type returned from scanBarcode
 @return barcode type name
 */
-(NSString *)barcodeType2Text:(int)barcodeType;

/**
 Starts barcode engine.
 In single scan mode the laser will be on until barcode is successfully read, the timeout elapses (set via call to barcodeSetScanTimeout) or if barcodeStopScan is called.
 In multi scan mode the laser will stay on even if barcode is successfully read allowing series of barcodes to be scanned within a single read session. The scanning will stop if no barcode is scanned in the timeout interval (set via call to barcodeSetScanTimeout) or if barcodeStopScan is called.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeStartScan:(NSError **)error;

/**
 Stops ongoing scan started with barcodeStartScan
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeStopScan:(NSError **)error;

/**
 Returns the current scan timeout. See barcodeSetScanTimeout for more detailed description.
 This setting is not persistent and is best to configure it upon connect.
 @param timeout returns scan timeout in seconds
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeGetScanTimeout:(int *)timeout error:(NSError **)error;

/**
 Sets the scan timeout. This it the max time that the laser will be on in single scan mode, or the time without scanning that will force the laser off in multi scan mode.
 This setting is not persistent and is best to configure it upon connect.
 @param timeout barcode engine timeout in seconds [1-60] or 0 to disable timeout. Default is 0
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeSetScanTimeout:(int)timeout error:(NSError **)error;

/**
 Returns the current scan button mode. See barcodeSetScanButtonMode for more detailed description.
 This setting is not persistent and is best to configure it upon connect.
 @param mode returns scan button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's button will become inactive</td></tr>
 <tr><td>BUTTON_ENABLED</td><td>Linea's button will triger barcode scan when pressed</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeGetScanButtonMode:(int *)mode error:(NSError **)error;

/**
 Sets Linea's scan button mode.
 This setting is not persistent and is best to configure it upon connect.
 @param mode button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's button will become inactive</td></tr>
 <tr><td>BUTTON_ENABLED</td><td>Linea's button will triger barcode scan when pressed</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeSetScanButtonMode:(int)mode error:(NSError **)error;

/**
 Sets Linea's beep, which is used upon successful barcode scan. This setting is not persistent and is best to configure it upon connect.
 @note  A sample beep containing of 2 tones, each with 400ms duration, first one 2000Hz and second - 5000Hz will look int beepData[]={2000,400,5000,400}
 @param enabled turns on or off beeping
 @param volume controls the volume (0-100). Currently have no effect
 @param data an array of integer values specifying pairs of tone(Hz) and duration(ms).
 @param length length in bytes of beepData array
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeSetScanBeep:(BOOL)enabled volume:(int)volume beepData:(int *)data length:(int)length error:(NSError **)error;


/**
 Returns the current scan mode.
 This setting is not persistent and is best to configure it upon connect.
 @param mode returns scanning mode, one of the MODE_* constants
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeGetScanMode:(int *)mode error:(NSError **)error;


/**
 Sets Linea's barcode engine scan mode.
 This setting is not persistent and is best to configure it upon connect.
 @param mode scanning mode, one of the MODE_* constants
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeSetScanMode:(int)mode error:(NSError **)error;

/**
 Enables or disables reading of specific barcode type.
 This setting is stored into the flash memory and will persists.
 @param barcodeType barcode type, one of the BAR_* constants with the exception of BAR_LAST. You can use BAR_ALL to enable or disable all barcode types at once
 @param enabled enables or disables reading of that barcode type
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeEnableBarcode:(int)barcodeType enabled:(BOOL)enabled error:(NSError **)error;

/**
 Returns if the the engine is set to read the barcode type or not.
 @param type barcode type, one of the BAR_* constants with the exception of BAR_ALL and BAR_LAST
 @return TRUE if the barcode is enabled
 */
-(BOOL)barcodeIsBarcodeEnabled:(int)type;


/**
 Returns if the the engine can read the barcode type or not.
 @param type barcode type, one of the BAR_* constants with the exception of BAR_ALL and BAR_LAST
 @return TRUE if the barcode is supported
 */
-(BOOL)barcodeIsBarcodeSupported:(int)type;


/**
 Returns the current barcode type mode. See barcodeSetTypeMode for more detailed description.
 This setting will not persists.
 @param mode returns barcode type mode, one of the:
 <table>
 <tr><td>BARCODE_TYPE_DEFAULT</td><td>default barcode types, listed in BARCODES enumeration</td></tr>
 <tr><td>BARCODE_TYPE_EXTENDED</td><td>extended barcode types, listed in BARCODES_EX enumeration</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeGetTypeMode:(int *)mode error:(NSError **)error;

/**
 Sets barcode type mode. Linea can return barcode type from the default list (listed in BARCODES) or extended one (listed in BARCODES_EX). The extended one is superset to the default, so current programs will be mostly unaffected if they switch from default to extended (with the exception of barcodes like UPC-A and UPC-E, which will be returned as UPC in the default list, but proper types in the extended. This setting will not persists.
 @param mode barcode type mode, one of the:
 <table>
 <tr><td>BARCODE_TYPE_DEFAULT (default)</td><td>default barcode types, listed in BARCODES enumeration</td></tr>
 <tr><td>BARCODE_TYPE_EXTENDED</td><td>extended barcode types, listed in BARCODES_EX enumeration</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeSetTypeMode:(int)mode error:(NSError **)error;

/**
 Allows basic control over the power to the barcode engine. By default Linea manages barcode engine by turning it on when scan operation is needed, then turning off after 5 seconds of inactivity. There are situations, where barcode engine should stay on to give better user experience, namely when using 2D barcode engine, which takes 1.7 seconds to start. This function is ignored for 1D barcode engines.
 
 <br>Be cautious using this function, if you pass TRUE to engineOn, the barcode engine will not turn off unless Linea is disconnected, program closes connection or iPod/iPhone goes to sleep, so it can drain the battery.
 
 <br>This setting does not persist, it is valid for current session only.
 @param engineOn TRUE will keep the engine powered on until the function is called with FALSE. In case of FALSE, Linea will work the usual way - powers on the engine just before scan operation.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeEnginePowerControl:(BOOL)engineOn error:(NSError **)error;

/**
 Allows basic control over the power to the barcode engine. By default Linea manages barcode engine by turning it on when scan operation is needed, then turning off after 5 seconds of inactivity. There are situations, where barcode engine should stay on to give better user experience, namely when using 2D barcode engine, which takes 1.7 seconds to start. This function is ignored for 1D barcode engines.
 
 <br>Be cautious using this function, if you pass TRUE to engineOn, the barcode engine will not turn off unless Linea is disconnected, program closes connection or iPod/iPhone goes to sleep, so it can drain the battery.
 
 <br>This setting does not persist, it is valid for current session only.
 @param engineOn TRUE will keep the engine powered on until the function is called with FALSE. In case of FALSE, Linea will work the usual way - powers on the engine just before scan operation.
 @param maxTimeMinutes the maximum idle time the engine will be kept on, in minutes. After that time elapses, the engine will be turned off to conserve power. Recommended value - 60 min. Setting the time is supported only on version 2.64 and later, on older firmware versions the time parameter is ignored.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeEnginePowerControl:(BOOL)engineOn maxTimeMinutes:(int)maxTimeMinutes error:(NSError **)error;

/**
 Performs factory reset of the barcode module. This function is taxing, slow and should not be called often, emergency use only.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeEngineResetToDefaults:(NSError **)error;

/**
 Allows for a custom initialization string to be sent to the Opticon barcode engine. The string is sent directly, if the barcode is currently powered on, and every time it gets initialized. The setting does not persists, so it is best this command is called upon new connection with Linea.
 @param data barcode engine initialization data (consult barcode engine manual)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 **/
-(BOOL)barcodeOpticonSetInitString:(NSString *)data error:(NSError **)error;

/**
 Sends configuration parameters directly to the opticon barcode engine. Use this function with EXTREME care, you can easily render your barcode engine useless. Refer to the barcode engine documentation on supported commands.
 
 <br>The function encapsulates the data with the ESC and CR so you don't have to send them. It optionally sends Z2 after the command to ensure settings are stored in the flash.
 
 <br>You can send multiple parameters with a single call if you format them as follows:
 - commands that take 2 symbols can be sent without any delimiters, like: "C1C2C3"
 - commands that take 3 symbols should be prefixed by [, like: "C1[C2AC3" (in this case commands are C1, C2A and C3
 - commands that take 4 symbols should be prefixed by ], like: "C1C2]C3AB" (in this case commands are C1, C2 and C3AB
 @param data command string
 @param saveToFlash if TRUE, command also saves the settings to flash. Saving setting is slower, so should be in ideal case executed only once and the program to remember it. The scanner's power usually gets cut when Linea goes to sleep - 5 seconds of idle time, so any non-stored to flash settings are lost, but if barcodeEnginePowerControl:TRUE is used on 2D engine, then even non-saved to flash settings will persist until device disconnects (iOS goes to sleep, physical disconnect)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeOpticonSetParams:(NSString *)data saveToFlash:(BOOL)saveToFlash error:(NSError **)error;

/**
 Reads barcode engine's identification
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return opticon engine ident string if function succeeded, nil otherwise
 */
-(NSString *)barcodeOpticonGetIdent:(NSError **)error;

/**
 Performs firmware update on the optiocon 2D barcode engines. Barcode update can take very long time, it is best to call this function from a thread and update
 the user interface when firmwareUpdateProgress delegate is called
 @param firmwareData firmware file data to load
 @param bootloader TRUE if you are going to update bootloader, FALSE if normal firmware
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeOpticonUpdateFirmware:(NSData *)firmwareData bootLoader:(BOOL)bootLoader error:(NSError **)error;

/**
 Sends configuration parameters directly to the code barcode engine. Use this function with EXTREME care,
 you can easily render your barcode engine useless. Refer to the barcode engine documentation for supported parameters.
 @param setting the setting number
 @param value the value to write to
 @return TRUE if operation was successful
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeCodeSetParam:(int)setting value:(uint64_t)value error:(NSError **)error;

/**
 Reads configuration parameters directly from the code barcode engine. Refer to the barcode engine documentation for supported parameters.
 @param setting the setting number
 @param value unpon success, the parameter value will be stored here
 @return TRUE if operation was successful
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeCodeGetParam:(int)setting value:(uint64_t *)value error:(NSError **)error;

/**
 Performs firmware update on the Code 2D barcode engines. Barcode update can take very long time, it is best to call this function from a thread and update
 the user interface when firmwareUpdateProgress delegate is called
 @param name the exact name of the firmware file
 @param firmwareData firmware file data to load
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)barcodeCodeUpdateFirmware:(NSString *)name data:(NSData *)data error:(NSError **)error;

-(NSDictionary *)barcodeCodeGetInformation:(NSError **)error;

/**
 Allows for a custom initialization string to be sent to the Intermec barcode engine. The data is sent directly, if the barcode is currently powered on, and every time it gets initialized. The setting does not persists, so it is best this command is called upon new connection with Linea.
 @param data barcode engine initialization data (consult barcode engine manual)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 **/
-(BOOL)barcodeIntermecSetInitData:(NSData *)data error:(NSError **)error;


/**@}*/


/** @defgroup G_LNCRYPTO Cryptographic & Security Functions
 Starting from firmware 2.13, Linea provides strong cryptographic support for magnetic card data. The encryption is supported on all Linea devices, from software point of view they are all the same, but provide different levels of hardware/firmware security.
 
 <br>An overview of the security, provided by Linea (see each of the crypto functions for further detail):
 
 <br>Hardware/Firmware:
 
 <br>For magnetic card encryption Linea is using AES256, which is the current industry standard encryption algorithm. The encryption key resides in volatile, battery powered ram inside Linea's cpu (for Linea 1.5 onward) and is being lost if anyone tries to break in the Linea device in order to prevent the key from being stolen. Magnetic card data, along with device serial number and some random bytes (to ensure every packet will be different) are being sent to the iOS program in an encrypted way.
 
 
 <br>Software:
 
 <br>Currently there are 2 types of keys, that can be loaded into Linea:
 - AUTHENTICATION KEY - used for device authentication (for example the program can lock itself to work with very specific Linea device) and encryption of the firmware
 - ENCRYPTION KEY - used for magnetic card data encryption. To use msr encryption, you don't need to set the AUTHENTICATION KEY.
 
 <br>Keys: The keys can be set/changed in two ways:
 
 <br>1. Using plain key data - this method is easy to use, but less secure, as it relies on program running on iPod/iPhone to have the key inside, an attacker could compromise the system and extract the key from device's memory. Call cryptoSetKey to set the keys this way. If there is an existing key of the same type inside Linea, you have to pass it too.
 
 <br>2. Using encrypted key data - this method is harder to implement, but provides better security - the key data, encrypted with old key data is sent from a server in secure environment to the program, running on the iOS, then the program forwards it to the Linea. The program itself have no means to decrypt the data, so an attacker can't possibly extract the key. Refer to cryptoSetKey documentation for more detailed description of the loading process.
 
 <br>The initial loading of the keys should always be done in a secure environment.
 
 <br>Magnetic card encryption:
 
 <br>Once ENCRYPTION KEY is set, all magnetic card data gets encrypted, and is now sent via magneticCardEncryptedData instead. The LineaDemo program contains sample code to decrypt the data block and extract the contents - the serial number and track data.
 
 <br>As with keys, card data can be extracted on the iOS device itself (less secure, the application needs to have the key inside) or be sent to a secure server to be processed. Note, that the encrypted data contains Linea's serial number too, this can be used for Data Origin Verification, to be sure someone is not trying to mimic data, coming from another device.
 
 
 <br>Demo program: the sample program now have "Crypto" tab, where key management can be tested:
 
 - New AES 256 key - type in the key you want to set (or change to)
 - Old AES 256 key - type in the previous key, or leave blank if you set the key for the first time
 
 <br>[SET AUTHENTICATION KEY] and [SET ENCRYPTION KEY] buttons allow you to use the key info in the text fields above to set the key.
 
 - Decryption key - type in the key, which the demo program will use to try to decrypt card data. This field should contain the
 ENCRYPTION KEY, or something random, if you want to test failed card data decryption.
 @ingroup G_LINEA
 @{
 */

/**
 Generates 16 byte block of random numbers, required for some of the other crypto functions.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return 16 bytes of random numbers if function succeeded, nil otherwise
 */
-(NSData *)cryptoRawGenerateRandomData:(NSError **)error;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys to reside on the device, but all the operations can be execuded with data, sent from a secure server. See cryptoSetKey if you plan to use the key in the mobile device.
 
 <br>Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or magneticCardEncryptedRawData
 
 <br>Generally the key loading process, using "Raw" commands, a program on the iOS device and a server which holds the keys will look similar to:
 
 - (iOS program) calls cryptoRawGenerateRandomData to get 16 bytes block of random data and send these to the server
 - (Server) creates byte array of 48 bytes consisting of: [RANDOM DATA: 16 bytes][KEY DATA: 32 bytes]
 - (Server) if there is current encryption key set on the Linea (if you want to change existing key) the server encrypts the 48 bytes block with the OLD key
 - (Server) sends the result data back to the program
 - (iOS program) calls cryptoRawSetKey with KEY_ENCRYPTION and the data it received from the server
 - (Linea) tries to decrypt the key data if there was already key present, then extracts the key, verifies the random data and if everything is okay, sets the key
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param encryptedData - 48 bytes that consists of 16 bytes random numbers received via call to cryptoRawGenerateRandomData and 32 byte AES256 key. If there has been previous key of the same type, then all 48 bytes should be encrypted with it.
 @param keyVersion - the version of the key. On firmware versions less than 2.43 this parameter is ignored and key version is considered to be 0x00000000. Key version is useful for the program to determine what key is inside the head.
 @param keyFlags - optional key flags, supported on ver 2.58 and onward
 - KEY_AUTHENTICATION:
 <table>
 <tr><td>BIT 1</td><td>If set to 1, scanning barcodes, reading magnetic card and using the bluetooth module are locked and have to be unlocked with cryptoAuthenticateHost/cryptoRawAuthenticateHost upon every reinsert of the device</td></tr>
 </table>
 - KEY_ENCRYPTION: No flags are supported
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)cryptoRawSetKey:(int)keyID encryptedData:(NSData *)encryptedData keyVersion:(uint32_t)keyVersion keyFlags:(uint32_t)keyFlags error:(NSError **)error;

/**
 Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or magneticCardEncryptedRawData
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param key 32 bytes AES256 key to set
 @param oldKey 32 bytes AES256 key that was previously used, or null if there was no previous key. The old key should match the new key, i.e. if you are setting KEY_ENCRYPTION, then you should pass the old KEY_ENCRYPTION.
 @param keyVersion - the version of the key. On firmware versions less than 2.43 this parameter is ignored and key version is considered to be 0x00000000. Key version is useful for the program to determine what key is inside the head.
 @param keyFlags - optional key flags, supported on ver 2.58 and onward
 - KEY_AUTHENTICATION:
 <table>
 <tr><td>BIT 1</td><td>If set to 1, scanning barcodes, reading magnetic card and using the bluetooth module are locked and have to be unlocked with cryptoAuthenticateHost/cryptoRawAuthenticateHost upon every reinsert of the device</td></tr>
 </table>
 - KEY_ENCRYPTION: No flags are supported
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)cryptoSetKey:(int)keyID key:(NSData *)key oldKey:(NSData *)oldKey keyVersion:(uint32_t)keyVersion keyFlags:(uint32_t)keyFlags error:(NSError **)error;

/**
 Returns key version. Valid key ID:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or magneticCardEncryptedRawData
 @param keyVersion returns key version or 0 if the key is not present (key versions are available in firmware 2.43 or later)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)cryptoGetKeyVersion:(int)keyID keyVersion:(uint32_t *)keyVersion error:(NSError **)error;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys to reside on the device, but all the operations can be execuded with data, sent from a secure server. See cryptoAuthenticateDevice if you plan to use the key in the mobile device.
 
 <br>Encrypts a 16 bytes block of random data with the stored authentication key and returns the result.
 
 <br>The idea: if a program wants to work with specific Linea device, it sets AES256 authentication key once, then on every connect the program generates random 16 byte block of data, encrypts it internally with the said key, then encrypts it with linea too and compares the result. If that Linea contains no key, or the key is different, the resulting data will totally differ from the one generated. This does not block Linea from operation, what action will be taken if devices mismatch depends on the program.
 @param randomData 16 bytes block of data (presumably random bytes)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return random data, encrypted with the Linea authentication key if function succeeded, nil otherwise
 */
-(NSData *)cryptoRawAuthenticateDevice:(NSData *)randomData error:(NSError **)error;

/**
 @note Check out the cryptoRawAuthenticateDevice function, if you want to not use the key inside the mobile device.
 
 <br>Generates random data, uses the key to encrypt it, then encrypts the same data with the stored authentication key inside Linea and returns true if both data matches.
 
 <br>The idea: if a program wants to work with specific Linea device, it sets AES256 authentication key once, then on every connect the program uses cryptoAuthenticateDevice with that key. If Linea contains no key, or the key is different, the function will return FALSE. This does not block Linea from operation, what action will be taken if devices mismatch depends on the program.
 @param key 32 bytes AES256 key
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if if Linea contains the same authentication key, FALSE otherwise
 */
-(BOOL)cryptoAuthenticateDevice:(NSData *)key error:(NSError **)error;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys to reside on the device, but all the operations can be execuded with data, sent from a secure server. See cryptoAuthenticateHost if you plan to use the key in the mobile device.
 
 <br>Tries to decrypt random data, generated from cryptoRawGenerateRandomData with the stored internal authentication key and returns the result. This function is used so that Linea knows a "real" device is currently connected, before allowing some functionality. Currently firmware update is protected by this function, once authentication key is set, you have to use it or cryptoAuthenticateHost before you attempt firmware update, or it will error out.
 
 <br>The idea (considering the iOS device does not have the keys inside, but depends on server):
 - (iOS program) generates random data using cryptoRawGenerateRandomData and sends to the server
 - (Server) encrypts the random data with the same AES256 key that is in the Linea and sends back to the iOS program
 - (iOS program) uses cryptoRawAuthenticateHost to authenticate with the data, an exception will be generated if authentication fails.
 @param encryptedRandomData 16 bytes block of encrypted data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)cryptoRawAuthenticateHost:(NSData *)encryptedRandomData error:(NSError **)error;

/**
 @note Check out the cryptoRawAuthenticateHost function, if you want to not use the key inside the mobile device.
 
 Generates random data, uses the key to encrypt it, then sends to Linea to verify against it's internal authentication key. If both keys match, return value is TRUE. This function is used so that Linea knows a "real" device is currently connected, before allowing some functionality. Currently firmware update is protected by this function, once authentication key is set, you have to use it or cryptoRawAuthenticateHost before you attempt firmware update, or it will error out.
 @param key 32 bytes AES256 key
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if Linea contains the same authentication key, FALSE otherwise
 */
-(BOOL)cryptoAuthenticateHost:(NSData *)key error:(NSError **)error;
/**@}*/



/*******************************************************************************
 * BLUETOOTH COMMANDS
 *******************************************************************************/
/** @defgroup G_LNBLUETOOTH Bluetooth Functions
 Functions to work with Linea's built-in bluetooth module
 @ingroup G_LINEA
 @{
 */
/**
 Returns bluethooth module status.
 @note When bluetooth module is enabled, access to the barcode engine is not possible!
 @param enabled returns TRUE if bluetooth module is enabled, FALSE otherwise
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btGetEnabled:(BOOL *)enabled error:(NSError **)error;

/**
 Enables or disables bluetooth module. Disabling the bluetooth module is currently the way to break existing bluetooth connection.
 @note When bluetooth module is enabled, access to the barcode engine is not possible!
 @param enabled TRUE to enable the engine, FALSE to disable it
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btSetEnabled:(BOOL)enabled error:(NSError **)error;

/**
 Sends data to the connected remote device.
 @note You can use bluethooth streams instead
 @param data data bytes to write
 @param length the length of the data in the buffer
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btWrite:(void *)data length:(int)length error:(NSError **)error;

/**
 Sends data to the connected remote device.
 @note You can use bluethooth streams instead
 @param data data string to write
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btWrite:(NSString *)data error:(NSError **)error;

/**
 Tries to read data from the connected remote device for specified timeout.
 @note You can use bluethooth streams instead
 @param data data buffer, where the result will be stored
 @param length maximum amount of bytes to wait for
 @param timeout maximim timeout in seconds to wait for data
 @return the
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return actual number of bytes stored in the data buffer if function succeeded, -1 otherwise
 */
-(int)btRead:(void *)data length:(int)length timeout:(double)timeout error:(NSError **)error;

/**
 Tries to read string data, ending with CR/LF up to specifed timeout
 @note You can use bluethooth streams instead
 @param timeout maximim timeout in seconds to wait for data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return string with the line read (can be empty string too) if function succeeded, nil otherwise
 */
-(NSString *)btReadLine:(double)timeout error:(NSError **)error;

/**
 Retrieves local bluetooth name, this is the name that Linea will report to bluetooth discovery requests.
 @note this function cannot be called once connection to remote device was established
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return bluetooth name if function succeeded, nil otherwise
 */
-(NSString *)btGetLocalName:(NSError **)error;

/**
 Performs synchronous discovery of the nearby bluetooth devices. This function is not recommended to be called on the main thread, use btDiscoverDevicesInBackground instead.
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param codTypes bluetooth Class Of Device to look for or 0 to search for all bluetooth devices
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return array of strings of bluetooth addresses if function succeeded, nil otherwise
 */
-(NSArray *)btDiscoverDevices:(int)maxDevices maxTime:(double)maxTime codTypes:(int)codTypes error:(NSError **)error;

/**
 Queries device name given the address, this function complements the btDiscoverDevices/btDiscoverPrinters and as such is not recommended, use btDiscoverDevicesInBackground instead.
 @note this function cannot be called once connection to remote device was established
 @param address bluetooth address returned from btDiscoverDevices/btDiscoverPrinters
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return bluetooth device name if function succeeded, nil otherwise
 */
-(NSString *)btGetDeviceName:(NSString *)address error:(NSError **)error;

/**
 Performs background discovery of nearby bluetooth devices. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param codTypes bluetooth Class Of Device to look for or 0 to search for all bluetooth devices
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDiscoverDevicesInBackground:(int)maxDevices maxTime:(double)maxTime codTypes:(int)codTypes error:(NSError **)error;

/**
 Performs background discovery of nearby supported bluetooth devices. Supported devices are the ones some of the sdks has built-in support for - printers and pinpads.
 The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param filter filter of which devices to discover, a combination of one or more of BLUETOOT_FILTER_* constants or BLUETOOTH_FILTER_ALL to get all supported devices
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDiscoverSupportedDevicesInBackground:(int)maxDevices maxTime:(double)maxTime filter:(int)filter error:(NSError **)error;

/**
 Performs discovery of supported printers. These include PP-60, DPP-250, DPP-350, SM-112, DPP-450.
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return array of strings containing bluetooth device address and bluetooth device name, i.e. if 2 devices are found, the list will contain @"address 1",@"name 1",@"address 2",@"name 2" if function succeeded, nil otherwise
 */
-(NSArray *)btDiscoverPrinters:(int)maxDevices maxTime:(double)maxTime error:(NSError **)error;

/**
 Performs background discovery of supported printers. These include PP-60, DPP-250, DPP-350, SM-112, DPP-450. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return, default is 4
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDiscoverPrintersInBackground:(int)maxDevices maxTime:(double)maxTime error:(NSError **)error;

/**
 Performs background discovery of supported printers. These include PP-60, DPP-250, DPP-350, SM-112, DPP-450. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDiscoverPrintersInBackground:(NSError **)error;

/**
 Performs discovery of supported pinpads. These include MPED-400 and PPAD1.
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return array of strings containing bluetooth device address and bluetooth device name, i.e. if 2 devices are found, the list will contain @"address 1",@"name 1",@"address 2",@"name 2" if function succeeded, nil otherwise
 */
-(NSArray *)btDiscoverPinpads:(int)maxDevices maxTime:(double)maxTime error:(NSError **)error;

/**
 Performs background discovery of supported printers. These include MPED-400 and PPAD1. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return, default is 4
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDiscoverPinpadsInBackground:(int)maxDevices maxTime:(double)maxTime error:(NSError **)error;

/**
 Performs background discovery of supported printers. These include MPED-400 and PPAD1. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDiscoverPinpadsInBackground:(NSError **)error;

/**
 Tries to connect to remote device. Once connection is established, use bluetooth streams to read/write to the remote device.
 @note this function cannot be called once connection to remote device was established
 @param address bluetooth address returned from btDiscoverDevices/btDiscoverPrinters
 @param pin PIN code if needed, or nil to try unencrypted connection
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btConnect:(NSString *)address pin:(NSString *)pin error:(NSError **)error;

/**
 Disconnects from remote device. Currently, due to bluetooth module limitation disconnect actually performs module power off and on, so the remote device may still hold on connected state for a while
 @param address bluetooth address returned from btDiscoverDevices/btDiscoverPrinters
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btDisconnect:(NSString *)address error:(NSError **)error;

/**
 Enables or disables write caching on the bluetooth stream. When enabled the writes gets cached and send on bigger chunks, reducing substantially the time taken, if you are sending lot of data in small parts.
 Write caching has negative effect on the speed if your bluetooth communication is based on request/response format or packets, in this case every write operation will get delayed, resulting in very poor throughput.
 @param enable enable or disable write caching, by default it is disabled
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)btEnableWriteCaching:(BOOL)enabled error:(NSError **)error;

/**
 Sets the conditions to fire the NSStreamEventHasBytesAvailable event on bluetooth streams. If all special conditions are disabled, then the notification will be fired the moment data arrives.
 You can have multiple notifications active at the same time, for example maxBytes and maxTime.
 @param maxTime notification will be fired 'maxTime' seconds after the last byte arrives, passing 0 disables it. For example 0.1 means that 100ms after the last byte is received the notification will fire.
 @param maxLength notification will be fired after 'maxLength' data arrives, passing 0 disables it.
 @param sequenceData notification will be fired if the received data contains 'sequenceData', passing nil disables it.
 */
-(BOOL)btSetDataNotificationMaxTime:(double)maxTime maxLength:(int)maxLength sequenceData:(NSData *)sequenceData error:(NSError **)error;

/**
 Bluetooth input stream, you can use it after connecting with btConnect. See NSInputStream documentation.
 **/
@property(assign, readonly) NSInputStream *btInputStream;

/**
 Bluetooth output stream, you can use it after connecting with btConnect. See NSOutputStream documentation.
 **/
@property(assign, readonly) NSOutputStream *btOutputStream;

/**@}*/

/*******************************************************************************
 * EXTERNAL SERIAL PORT COMMANDS
 *******************************************************************************/
/** @defgroup G_LESERIAL External Serial Port Functions
 Functions to work with Linea Tab's external serial port
 @ingroup G_LINEA
 @{
 */

/**
 Opens the external serial port with specified settings.
 @note On Linea Tab opening the serial port disables barcode scanner for the duration
 @param port the port number, currently only 1 is used
 @param baudRate serial baud rate
 @param parity serial parity, one of the PARITY_* constants (currenty only PARITY_NONE is supported)
 @param dataBits serial data bits, one of the DATABITS_* constants (currently only DATABITS_8 is supported)
 @param stopBits serial stop bits, one of the STOPBITS_* constants (currently only STOPBITS_1 is supported)
 @param flowControl serial flow control, one of the FLOW_* constants (currently only FLOW_NONE is supported)
 @param error returns error information, you can pass nil if you don't want it
 @return TRUE upon success, FALSE otherwise
 **/
-(BOOL)extOpenSerialPort:(int)port baudRate:(int)baudRate parity:(int)parity dataBits:(int)dataBits stopBits:(int)stopBits flowControl:(int)flowControl error:(NSError **)error;

/**
 Closes the external serial port opened with extOpenSerialPort
 @param port the port number, currently only 1 is used
 @param error returns error information, you can pass nil if you don't want it
 @return TRUE upon success, FALSE otherwise
 **/
-(BOOL)extCloseSerialPort:(int)port error:(NSError **)error;

/**
 Sends data to the connected remote device via serial port.
 @param port the port number, currently only 1 is used
 @param data data bytes to write
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)extWriteSerialPort:(int)port data:(NSData *)data error:(NSError **)error;

/**
 Reads data from the connected remote device via serial port.
 @param port the port number, currently only 1 is used
 @param length the maximum amount of data to read
 @param timeout timeout in seconds, passing 0 reads and returns the bytes currently in the buffer
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData with bytes received if function succeeded, nil otherwise
 */
-(NSData *)extReadSerialPort:(int)port length:(int)length timeout:(double)timeout error:(NSError **)error;

/**@}*/


/*******************************************************************************
 * ENCRYPTED MAGNETIC HEAD COMMANDS
 *******************************************************************************/
/** @defgroup G_LEMSR Encrypted Magnetic Head Functions
 Functions to work with Linea's optional encrypted magnetic head
 @ingroup G_LINEA
 @{
 */

#define LN_EMSR_EBASE -11000
/** Encrypted magnetic head invalid command sent. */
#define LN_EMSR_EINVALID_COMMAND LN_EMSR_EBASE-0x01
/** Encrypted magnetic head no permission error. */
#define LN_EMSR_ENO_PERMISSION LN_EMSR_EBASE-0x02
/** Encrypted magnetic head card error. */
#define LN_EMSR_ECARD LN_EMSR_EBASE-0x03
/** Encrypted magnetic head command syntax error. */
#define LN_EMSR_ESYNTAX LN_EMSR_EBASE-0x04
/** Encrypted magnetic head command no response from the magnetic chip. */
#define LN_EMSR_ENO_RESPONSE LN_EMSR_EBASE-0x05
/** Encrypted magnetic head no data available. */
#define LN_EMSR_ENO_DATA LN_EMSR_EBASE-0x06
/** Encrypted magnetic head invalid data length. */
#define LN_EMSR_EINVALID_LENGTH LN_EMSR_EBASE-0x14
/** Encrypted magnetic head is tampered. */
#define LN_EMSR_ETAMPERED LN_EMSR_EBASE-0x15
/** Encrypted magnetic head invalid signature. */
#define LN_EMSR_EINVALID_SIGNATURE LN_EMSR_EBASE-0x16
/** Encrypted magnetic head hardware failure. */
#define LN_EMSR_EHARDWARE LN_EMSR_EBASE-0x17


/**
 Returns information about the specified head firmware data. Based on it, and the current head's name and firmware version you can chose to update or not the head's firmware
 @param data - firmware data
 @return dictionary containing extracted data or nil if the data is invalid. Keys contained are:
 <table>
 <tr><td>"deviceModel"</td><td>Head's model, for example "EMSR-DEA"</td></tr>
 <tr><td>"firmwareRevision"</td><td>Firmware revision as string, for example 1.07</td></tr>
 <tr><td>"firmwareRevisionNumber"</td><td>Firmware revision as number MAJOR*100+MINOR, i.e. 1.07 will be returned as 107</td></tr>
 </table>
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 **/
-(NSDictionary *)emsrGetFirmwareInformation:(NSData *)data error:(NSError **)error;

/**
 Checks if the head was tampered or not. If the head's tamper protection have activated, the device should be sent to service for checks
 @return true if the head was tampered and not operational
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw LineaModuleInactiveException if there is no connection to the encrypted head
 */
-(BOOL)emsrIsTampered:(BOOL *)tampered error:(NSError **)error;

/**
 Retrieves the key version (if any) of a loaded key
 @param keyID the ID of the key to get the version, one of the KEY_* constants
 @param keyVersion - pointer to integer, where key version will be returned upon success. Key version can be 0.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrGetKeyVersion:(int)keyID keyVersion:(int *)keyVersion error:(NSError **)error;

/**
 Loads Terminal Master Key (TMK) or reenable after tampering. This command is enabled only if the device is in tamper mode or there is no TMK key yet. If the command is executed in normal mode an error will be returned. To reenable the device after tampering the old TMK key must be passed as an argument. If the keys do not match error will be returned.
 @param keyData an array, that consists of:
 - BLOCK IDENT - 1 byte, set to 0x29
 - KEY ID - the ID of the key to set, put KEY_TMK_AES (0x10)
 - KEY VERSION - the version of the key in high to low order, 4 bytes, cannot be 0
 - KEY - the key data, 16 bytes
 - HASH - SHA256 of the previous bytes (BLOCK IDENT, KEY ID, KEY VERSION and KEY)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrLoadInitialKey:(NSData *)keyData error:(NSError **)error;

/**
 Loads new key, in plain or encrypted with already loaded AES256 Key Encryption Key (KEK). Plain text loading works only the first time the specified key is loaded and is recommended only in secure environment. For normal usage the new key should be encrypted with the Key Encryption Key (KEK). The command is unavailable if the device is tampred.
 @param keyData an array, that consists of:
 - MAGIC NUMBER - (1 byte) 0x2b
 - ENCRYPTION KEY ID - (1 byte) the ID of the already existing key, used to encrypt the new key data. Set it to KEY_EH_AES256_LOADING (0x02) if you want to set the key in encrypted state or 0xFF for plain state.
 - KEY ID - (1 byte) the ID of the key to set, one of the KEY_ constants. The TMK cannot be changed with this command.
 - KEY VERSION - (4 bytes) the version of the key in high to low order, 4 bytes, cannot be 0
 - KEY - (variable) the key data, length depends on the key in question, AES256 keys are 32 bytes, DUKPT key is 16 bytes key, 10 bytes serial, 6 bytes for padding (zeroes)
 - HASH - SHA256 of the previous bytes (MAGIC NUMBER, ENCRYPTION KEY ID, KEY ID, KEY VERSION, KEY)
 
 <br>If using KEY_EH_AES256_LOADING, then KEY + HASH have to be put inside the packet encrypted with AES256 using key KEY_EH_AES256_LOADING. SHA256 is calculated on the unencrypted data. The head decrypts the data and then calculates and compares the hash. If the calculated SHA does not match the SHA sent with the command, the key excahnge is rejected and error is returned.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrLoadKey:(NSData *)keyData error:(NSError **)error;

/**
 Returns DUKPT serial number, if DUKPT key is set
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return serial number or nil if an error occured
 */
-(NSData *)emsrGetDUKPTSerial:(NSError **)error;

/**
 Returns head's model
 @return head's model as string
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(NSString *)emsrGetDeviceModel:(NSError **)error;

/**
 Returns head's firmware version as number MAJOR*100+MINOR, i.e. version 1.05 will be sent as 105
 @param version integer, where firmware version is stored upon success
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrGetFirmwareVersion:(int *)version error:(NSError **)error;

/**
 Returns head's security version as number MAJOR*100+MINOR, i.e. version 1.05 will be sent as 105. Security version is the version of the certificated security kernel.
 @param version integer, where firmware version is stored upon success
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrGetSecurityVersion:(int *)version error:(NSError **)error;

/**
 Return head's unique serial number as byte array
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return serial number or nil if an error occured
 */
-(NSData *)emsrGetSerialNumber:(NSError **)error;

/**
 Performs firmware update on the encrypted head.
 DO NOT INTERRUPT THE COMMUNICATION DURING THE FIRMWARE UPDATE!
 @param data firmware file data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrUpdateFirmware:(NSData *)data error:(NSError **)error;

/**
 Returns supported encryption algorhtms by the encrypted head.
 @param data firmware file data
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return an array of supported algorithms or nil if an error occured
 */
-(NSArray *)emsrGetSupportedEncryptions:(NSError **)error;

/**
 Selects the prefered encryption algorithm. When card is swiped, it will be encrypted by it and sent via magneticCardEncryptedData delegate
 @param encryption encryption algorhtm used, one o fthe ALG_* constants
 @param params optional algorithm parameters, currently no algorithm supports these
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrSetEncryption:(int)encryption params:(NSData *)params error:(NSError **)error;

/**
 Fine-tunes which part of the card data will be masked, and which will be sent in clear text for display/print purposes
 @param showExpiration if set to TRUE, expiration date will be shown in clear text, otherwise will be masked
 @param unmaskedDigitsAtStart the number of digits to show in clear text at the start of the PAN, range from 0 to 6 (default is 4)
 @param unmaskedDigitsAtEnd the number of digits to show in clear text at the end of the PAN, range from 0, to 4 (default is 4)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)emsrConfigMaskedDataShowExpiration:(BOOL)showExpiration unmaskedDigitsAtStart:(int)unmaskedDigitsAtStart unmaskedDigitsAtEnd:(int)unmaskedDigitsAtEnd error:(NSError **)error;

/**@}*/

/*******************************************************************************
 * RF READER COMMANDS
 *******************************************************************************/
/** @defgroup G_LNRFREADER RF Reader Functions
 Functions to work with the Linea's built-in RF cards reader
 @ingroup G_LINEA
 @{
 */

/**
 ISO14443 Type A (Mifare) cards will be detected
 */
#define CARD_SUPPORT_TYPE_A 0x0001
/**
 ISO14443 Type B cards will be detected. Currently unsupported.
 */
#define CARD_SUPPORT_TYPE_B 0x0002
/**
 Felica cards will be detected.
 */
#define CARD_SUPPORT_FELICA 0x0004
/**
 NFC cards will be detected. Currently unsupported.
 */
#define CARD_SUPPORT_NFC 0x0008
/**
 Jewel cards will be detected. Currently unsupported.
 */
#define CARD_SUPPORT_JEWEL 0x0010
/**
 ISO15693 cards will be detected
 */
#define CARD_SUPPORT_ISO15 0x0020

/**
 Initializes and powers on the RF card reader module. Call this function before any other RF card functions. The module power consumption is highly optimized, so it can be left on for extended periods of time.
 @param supportedCards any combination of CARD_SUPPORT_* flags to mark which card types to be active. Enable only cards you actually plan to work with, this has high implication on power usage and detection speed.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)rfInit:(int)supportedCards error:(NSError **)error;
/**
 Powers down RF card reader module. Call this function after you are done with the reader.
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)rfClose:(NSError **)error;
/**
 Call this function once you are done with the card, a delegate call rfCardRemoved will be called when the card leaves the RF field and new card is ready to be detected
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)rfRemoveCard:(int)cardIndex error:(NSError **)error;
/**
 Authenticate mifare card block with direct key data. This is less secure method, as it requires the key to be present in the program, the prefered way is to store a key once in a secure environment and then authenticate using the stored key.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param type key type, either 'A' or 'B'
 @param address the address of the block to authenticate
 @param key 6 bytes key
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfAuthByKey:(int)cardIndex type:(char)type address:(int)address key:(NSData *)key error:(NSError **)error;
/**
 Store key in the internal module memory for later use
 @param keyIndex the index of the key, you can have up to 8 keys stored (0-7)
 @param type key type, either 'A' or 'B'
 @param key 6 bytes key
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfStoreKeyIndex:(int)keyIndex type:(char)type key:(NSData *)key error:(NSError **)error;
/**
 Authenticate mifare card block with previously stored key. This the prefered method, as no key needs to reside in application.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param type key type, either 'A' or 'B'
 @param address the address of the block to authenticate
 @param keyIndex the index of the stored key, you can have up to 8 keys stored (0-7)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfAuthByStoredKey:(int)cardIndex type:(char)type address:(int)address keyIndex:(int)keyIndex error:(NSError **)error;
/**
 Reads one more more blocks of data from Mifare Classic/Ultralight cards. A single read operation gets 16 bytes of data, so you can pass 32 on length to read 2 blocks, etc
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the block to read
 @param length the number of bytes to read, this must be multiple of block size (16 bytes)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)mfRead:(int)cardIndex address:(int)address length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to Mifare Classic/Ultralight cards. A single write operation stores 16 bytes of data, so you can pass 32 on length to write 2 blocks, etc
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the block to write
 @param data the data to write, must be multiple of the block size (16 bytes)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)mfWrite:(int)cardIndex address:(int)address data:(NSData *)data error:(NSError **)error;
/**
 Sets the 3DES key of Mifare Ultralight C cards
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param key 16 bytes 3DES key to set
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfUlcSetKey:(int)cardIndex key:(NSData *)key error:(NSError **)error;
/**
 Performs 3DES authentication of Mifare Ultralight C card using the given key
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param key 16 bytes 3DES key to authenticate with
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)mfUlcAuthByKey:(int)cardIndex key:(NSData *)key error:(NSError **)error;

/**
 Reads one more more blocks of data from ISO 15693 card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to read from
 @param length the number of bytes to read, this must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)iso15693Read:(int)cardIndex startBlock:(int)startBlock length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to ISO 15693 card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to write to
 @param data the data to write, it must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)iso15693Write:(int)cardIndex startBlock:(int)startBlock data:(NSData *)data error:(NSError **)error;
/**
 Reads the security status of one more more blocks from ISO 15693 card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to read from
 @param nBlocks the number of blocks to get the security status
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)iso15693GetBlocksSecurityStatus:(int)cardIndex startBlock:(int)startBlock nBlocks:(int)nBlocks error:(NSError **)error;
/**
 Locks a single ISO 15693 card block. Locked blocks cannot be written upon anymore.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param block the block index to lock
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693LockBlock:(int)cardIndex block:(int)block error:(NSError **)error;
/**
 Changes ISO 15693 card AFI.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param afi new AFI value
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693WriteAFI:(int)cardIndex afi:(uint8_t)afi error:(NSError **)error;
/**
 Locks ISO 15693 AFI preventing further changes.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693LockAFI:(int)cardIndex error:(NSError **)error;
/**
 Changes ISO 15693 card DSFID.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param dsfid new DSFID value
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693WriteDSFID:(int)cardIndex dsfid:(uint8_t)dsfid error:(NSError **)error;
/**
 Locks ISO 15693 card DSFID preventing further changes.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)iso15693LockDSFID:(int)cardIndex error:(NSError **)error;

/**
 Reads one more more blocks of data from FeliCa card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to read from
 @param length the number of bytes to read, this must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)felicaRead:(int)cardIndex startBlock:(int)startBlock length:(int)length error:(NSError **)error;
/**
 Writes one more more blocks of data to FeliCa card.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param startBlock the starting block to write to
 @param data the data to write, it must be multiple of block size (can be taken from the card info that is coming with rfCardDetected call)
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)felicaWrite:(int)cardIndex startBlock:(int)startBlock data:(NSData *)data error:(NSError **)error;

/**
 Returns FeliCa SmartTag battery status
 @note Call this function before any other SmartTag
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param status upon successful execution, battery status will be returned here, one of FELICA_SMARTTAG_BATTERY_* constants
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagGetBatteryStatus:(int)cardIndex status:(int *)status error:(NSError **)error;
/**
 Clears the screen of FeliCa SmartTag
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param status upon successful execution, battery status will be returned here, one of FELICA_SMARTTAG_BATTERY_* constants
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagClearScreen:(int)cardIndex error:(NSError **)error;
/**
 Draws image on FeliCa SmartTag's screen. The screen is 200x96 pixels.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param image image to draw
 @param topLeftX - topleft X coordinate in pixels
 @param topLeftY - topleft Y coordinate in pixels
 @param drawMode draw mode, one of the FELICA_SMARTTAG_DRAW_* constants
 @param layout only used when drawMode is FELICA_SMARTTAG_DRAW_USE_LAYOUT, it specifies the index of the layout (1-12) of the previously stored image
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagDrawImage:(int)cardIndex image:(UIImage *)image topLeftX:(int)topLeftX topLeftY:(int)topLeftY drawMode:(int)drawMode layout:(int)layout error:(NSError **)error;
/**
 Saves the current display as layout number
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param layout layout index (1-12) to which the currently displayed image will be saved
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagSaveLayout:(int)cardIndex layout:(int)layout error:(NSError **)error;
/**
 Displays previously stored layout
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param layout layout index (1-12) of the previously stored image
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagDisplayLayout:(int)cardIndex layout:(int)layout error:(NSError **)error;
/**
 Writes data in FeliCa SmartTag.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the card to write to, refer to SmartTag documentation
 @param data data to write, note that the data does not need to be aligned to block size
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return number of bytes actually written or 0 if an error occured
 */
-(int)felicaSmartTagWrite:(int)cardIndex address:(int)address data:(NSData *)data error:(NSError **)error;
/**
 Writes data in FeliCa SmartTag.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param address the address of the card to read from, refer to SmartTag documentation
 @param length of the data to read, note that the data does not need to be aligned to block size
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return NSData object containing the data received or nil if an error occured
 */
-(NSData *)felicaSmartTagRead:(int)cardIndex address:(int)address length:(int)length error:(NSError **)error;
/**
 Waits for FeliCa SmartTag to complete current operation. Waiting is generally not needed, but needed in case for example drawing an image and then saving the layout, you need to wait for the image to be drawn.
 Write operation forces waiting internally.
 @param cardIndex the index of the card as sent by rfCardDetected delegate call
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)felicaSmartTagWaitCompletion:(int)cardIndex error:(NSError **)error;



/**@}*/

/**
 Adds delegate to the class
 **/
@property(assign) id delegate;

/**
 Provides a list of currently registered delegates
 */
@property(readonly) NSMutableArray *delegates;

/**
 Returns current connection state
 **/
@property(readonly) int connstate;
/**
 Returns connected device name
 **/
@property(assign, readonly) NSString *deviceName;
/**
 Returns connected device model
 **/
@property(assign, readonly) NSString *deviceModel;
/**
 Returns connected device firmware version
 **/
@property(assign, readonly) NSString *firmwareRevision;
/**
 Returns connected device hardware version
 **/
@property(assign, readonly) NSString *hardwareRevision;
/**
 Returns connected device serial number
 **/
@property(assign, readonly) NSString *serialNumber;

/**
 SDK version number in format MAJOR*100+MINOR, i.e. version 1.15 will be returned as 115
 */
@property(readonly) int sdkVersion;
/**@}*/

@end

/**@}*/

#ifndef LINEA_NO_EXCEPTIONS

#pragma mark DEPRECATED

#if !__has_feature(objc_arc)
#ifndef FINANCIALCARD_DEFINED
#define FINANCIALCARD_DEFINED
typedef struct
{
    NSString *accountNumber;
    NSString *cardholderName;
    int  expirationYear;
    int  expirationMonth;
    NSString *serviceCode;
    NSString *discretionaryData;
    NSString *firstName;
    NSString *lastName;
}financialCard;
#endif

typedef struct firmwareInfo
{
	NSString *deviceName;
	NSString *deviceModel;
	NSString *firmwareRevision;
	int		  firmwareRevisionNumber;
}firmwareInfo;
#endif

/** @defgroup G_DEP_LINEA Deprecated Linea Functions
 Deprecated functions, please check out NSError alternatives
 @{
 */

@interface Linea (LineaDeprecated)
/**
 Returns Linea's battery capacity in percent
 @note Reading battery voltages during charging (both Linea charing and Linea charging the iPod) is unreliable!
 @return Battery capacity in percent
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)getBatteryCapacity;

/**
 Returns Linea's battery voltage
 @note Reading battery voltages during charging (both Linea charing and Linea charging the iPod) is unreliable!
 @return Battery voltage in Volt*10, i.e. value of 45 means 4.5V
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)getBatteryVoltage;

/**
 Makes Linea plays a sound using the built-in speaker
 @param volume controls the volume (0-100). Currently have no effect
 @param data an array of integer values specifying pairs of tone(Hz) and duration(ms).
 @param length length in bytes of beepData array
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 @note A sample beep containing of 2 tones, each with 400ms duration, first one 2000Hz and second - 5000Hz
 will look int beepData[]={2000,400,5000,400}
 */
-(void)playSound:(int)volume beepData:(int *)data length:(int)length;

/**
 Returns if Linea is charging the iOS device from it's own battery. Linea firmware versions prior to 2.13 will return true
 if external charge is attached, 2.13 and later will return only if Linea's own battery is used for charging
 @return TRUE if charging is enabled.
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(BOOL)getCharging;

/**
 Enables or disables Lines's capability to charge the handheld from it's own battery. Charging can stop if Linea's battery goes too low.
 When enabling or disabling the charge linea will force disconnect and reconnect.
 
 <br>While Linea can act as external battery for the iPod/iPhone, there are certain limitations if you decide to implement it. The internal battery is
 not big enough, so if the iPod/iPhone consumes a lot of power from it, it will go down very fast and force the firmware to cut the charge to prevent
 going down to dangerous levels. The proper use of this charging function depends on how the program, running on the iPod/iPhone, is used and how the
 iPod/iPhone is discharged
 
 <br>There are two possible ways to use Linea's charge:
 - Emergency mode - in the case iPod/iPhone usage is designed in a way it will last long enough between charging sessions and using Linea's charge
 is not generally needed, the charge can be used if the iPod/iPhone for some reason goes too low (like <50%), so it is given some power to continue
 working until next charging. An example will be store, where devices are being charged every night, but extreme usage on some iPod drains
 the battery before the end of the shift.
 This is the less efficient way to charge it, also, Linea will refuse to start the charge if it's own battery goes below 3.8v, so depending on the usage,
 barcode type and if the barcode engine is set to work all the time, it may not be possible to start the charge.
 
 - Max life mode - it is the case where both devices are required to operate as long as possible. Usually, the iPod/iPhone's battery will be drained
 way faster than Linea's, especially with wifi enabled programs and to keep both devices operating as long as possible, the charging should
 be desinged in a way so iPod/iPhone is able to use most of Linea's battery. This is possible, if you start charging when iPod/iPhone is almost full - at around
 75-80% or higher. This way the iPod will consume small amount of energy, allowing our battery to slowly be used almost
 fully to charge it.
 
 <br>LineaDemo application contains sample implementation of max life mode charging.
 
 @note Reading battery voltages during charging is unreliable!
 @param enabled TRUE to enable charging, FALSE to disable/stop it
 @return TRUE if operation succeeded. Enabling charge can fail if Linea's battery is low. Disabling charge will fail if there is external charger or usb cable attached.
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)setCharging:(BOOL)enabled;

/**
 Returns information about the specified firmware file. Based on it, and the connected Linea's name, model and firmware version
 you can chose to update or not the Linea's firmware
 @param path the full path and file name where the firmware file is located
 @param info pointer to a structure, that will be filled with firmware file information - name, model and firmware version
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
#if !__has_feature(objc_arc)
-(void)getFirmwareFileInformation:(NSString *)path firmwareInfo:(struct firmwareInfo *)info;
#endif

/**
 Returns information about the specified firmware data. Based on it, and the connected Linea's name, model and firmware version
 you can chose to update or not the Linea's firmware
 @param data - firmware data
 @return dictionary containing extracted data or nil if the data is invalid. See Info* constants for possible key values.
 @throw NSPortTimeoutException if there is no connection to Linea
 **/
-(NSDictionary *)getFirmwareFileInformation:(NSData *)data;

/**
 Updates Linea's firmware with specified firmware file. The firmware can only be upgraded or downgraded, if you send
 the same firmware version, then no update process will be started.
 @param path the full path and file name where the firmware file is located
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if the firmware file is missing, can't be opened, damaged or contains invalid firmware version
 @note Make sure the user does not interrupt the process or the device will be rendered unusable and can only be recovered via
 the special firmware update cable
 */
-(void)updateFirmware:(NSString *)path;

/**
 Updates Linea's firmware with specified firmware data. The firmware can only be upgraded or downgraded, if you send
 the same firmware version, then no update process will be started.
 @param data the firmware data
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if the firmware file is missing, can't be opened, damaged or contains invalid firmware version
 @note Make sure the user does not interrupt the process or the device will be rendered unusable and can only be recovered via
 the special firmware update cable
 */
-(void)updateFirmwareData:(NSData *)data;

/**
 Returns the current sync button mode. See setSyncButtonMode for more detailed description.
 This setting is stored into flash memory and will persist.
 @return sync button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's will not perform synchronization when you press and hold the button for 3 seconds</td></tr>
 <tr><td>BUTTON_ENABLED</td><td>Linea's will perform synchronization when you press and hold the button for 3 seconds</td></tr>
 </table>
 @note Although this function was made for Linea 1, that had hardware button to enter sync mode, it still works for enabling/disabling automated sync on Linea 4 and onward
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)getSyncButtonMode;

/**
 Sets Linea's sync button mode.
 This setting is stored into flash memory and will persist.
 @param mode button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's will not perform synchronization when you press and hold the button for 3 seconds</td></tr>
 <tr><td>BUTTON_ENABLED (default)</td><td>Linea's will perform synchronization when you press and hold the button for 3 seconds</td></tr>
 </table>
 @note Although this function was made for Linea 1, that had hardware button to enter sync mode, it still works for enabling/disabling automated sync on Linea 4 and onward
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)setSyncButtonMode:(int)mode;
/**@}*/



/** @defgroup G_DEP_LNMSREADER Deprecated Magnetic Stripe Reader Functions
 Functions to work with the Linea's built-in magenetic card reader
 @ingroup G_DEP_LINEA
 @{
 */

/**
 Enables reading of magnetic cards. Whenever a card is successfully read, the magneticCardData delegate will be called.
 Current magnetic card heads used in Linea 1.0, 1.5 and 2.0 consume so little power, that there is no drawback in leaving
 scanning enabled all the time.
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(void)msEnable;

/**
 Disables magnetic card scanning started with msEnable
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(void)msDisable;

/**
 Helper function to parse financial card and extract the data - name, number, expiration date.
 The function will extract as much information as possible, fields not found will be set to nil/0.
 @param data - pointer to financialCard structure, where the extracted data will be stored
 @param track1 - track1 information or nil
 @param track2 - track2 information or nil
 @return TRUE if the card tracks represent valid financial card and data was extracted
 @throw NSPortTimeoutException if there is no connection to Linea
 **/
#if !__has_feature(objc_arc)
-(BOOL)msProcessFinancialCard:(financialCard *)data track1:(NSString *)track1 track2:(NSString *)track2;
#endif

/**
 Helper function to parse financial card and extract the data - name, number, expiration date.
 The function will extract as much information as possible.
 @param track1 - track1 information or nil
 @param track2 - track2 information or nil
 @return dictionary containing extracted data or nil if the data is invalid. Keys contained are:
 <table>
 <tr><td>"accountNumber"</td><td>Account number</td></tr>
 <tr><td>"cardholderName"</td><td>Cardholder name, as stored in the card</td></tr>
 <tr><td>"expirationYear"</td><td>Expiration date - year</td></tr>
 <tr><td>"expirationMonth"</td><td>Expiration date - month</td></tr>
 <tr><td>"serviceCode"</td><td>Service code (if any)</td></tr>
 <tr><td>"discretionaryData"</td><td>Discretionary data (if any)</td></tr>
 <tr><td>"firstName"</td><td>Extracted cardholder's first name</td></tr>
 <tr><td>"lastName"</td><td>Extracted cardholder's last name</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 **/
-(NSDictionary *)msProcessFinancialCard:(NSString *)track1 track2:(NSString *)track2;

/**
 Returns the current magnetic card data mode.
 This setting is not persistent and is best to configure it upon connect.
 @return card data mode, one of the:
 <table>
 <tr><td>MS_PROCESSED_CARD_DATA</td><td>Card data will be processed and will be returned via call to magneticCardData</td></tr>
 <tr><td>MS_RAW_CARD_DATA</td><td>Card data will not be processed and will be returned via call to magneticCardRawData</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)msGetCardDataMode;

/**
 Sets Linea's magnetic card data mode.
 This setting is not persistent and is best to configure it upon connect.
 @param mode magnetic card data mode:
 <table>
 <tr><td>MS_PROCESSED_CARD_DATA</td><td>Card data will be processed and will be returned via call to magneticCardData</td></tr>
 <tr><td>MS_RAW_CARD_DATA</td><td>Card data will not be processed and will be returned via call to magneticCardRawData</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)msSetCardDataMode:(int)mode;
/**@}*/



/** @defgroup G_DEP_LNBARCODEREADER Deprecated Barcode Reader Functions
 Functions for scanning barcodes, various barcode settings and direct control of the barcode engine
 @ingroup G_DEP_LINEA
 @{
 */

/**
 Helper function to return string name of barcode type
 @param barcodeType barcode type returned from scanBarcode
 @return barcode type name
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(NSString *)barcodeType2Text:(int)barcodeType;

/**
 Starts barcode engine.
 In single scan mode the laser will be on until barcode is successfully read, the timeout elapses
 (set via call to barcodeSetScanTimeout) or if barcodeStopScan is called.
 In multi scan mode the laser will stay on even if barcode is successfully read allowing series of
 barcodes to be scanned within a single read session. The scanning will stop if no barcode is scanned
 in the timeout interval (set via call to barcodeSetScanTimeout) or if barcodeStopScan is called.
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(void)barcodeStartScan;

/**
 Stops ongoing scan started with barcodeStartScan
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(void)barcodeStopScan;

/**
 Returns the current scan timeout. See barcodeSetScanTimeout for more detailed description.
 This setting is not persistent and is best to configure it upon connect.
 @return scan timeout in seconds
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)barcodeGetScanTimeout;

/**
 Sets the scan timeout. This it the max time that the laser will be on in
 single scan mode, or the time without scanning that will force the laser off in multi scan mode.
 This setting is not persistent and is best to configure it upon connect.
 @param timeout barcode engine timeout in seconds [1-60] or 0 to disable timeout. Default is 0
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)barcodeSetScanTimeout:(int)timeout;

/**
 Returns the current scan button mode. See barcodeSetScanButtonMode for more detailed description.
 This setting is not persistent and is best to configure it upon connect.
 @return scan button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's button will become inactive</td></tr>
 <tr><td>BUTTON_ENABLED</td><td>Linea's button will triger barcode scan when pressed</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)barcodeGetScanButtonMode;

/**
 Sets Linea's scan button mode.
 This setting is not persistent and is best to configure it upon connect.
 @param mode button mode, one of the:
 <table>
 <tr><td>BUTTON_DISABLED</td><td>Linea's button will become inactive</td></tr>
 <tr><td>BUTTON_ENABLED</td><td>Linea's button will triger barcode scan when pressed</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)barcodeSetScanButtonMode:(int)mode;

/**
 Sets Linea's beep, which is used upon successful barcode scan
 This setting is not persistent and is best to configure it upon connect.
 @param enabled turns on or off beeping
 @param volume controls the volume (0-100). Currently have no effect
 @param data an array of integer values specifying pairs of tone(Hz) and duration(ms).
 @param length length in bytes of beepData array
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 @note  A sample beep containing of 2 tones, each with 400ms duration, first one 2000Hz and second - 5000Hz will look int beepData[]={2000,400,5000,400}
 */
-(void)barcodeSetScanBeep:(BOOL)enabled volume:(int)volume beepData:(int *)data length:(int)length;

/**
 Returns the current scan mode.
 This setting is not persistent and is best to configure it upon connect.
 @return scanning mode, one of the:
 <table>
 <tr><td>MODE_SINGLE_SCAN</td><td>Linea will deactivate the laser after a successful barcode scan</td></tr>
 <tr><td>MODE_MULTI_SCAN</td><td>Linea will continue to scan even after successful barcode scan and will stop when scan button is released, barcodeStopScan command is sent or there is no barcode scaned for several seconds (set via call to barcodeSetScanTimeout)</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)barcodeGetScanMode;

/**
 Sets Linea's scan button mode.
 This setting is not persistent and is best to configure it upon connect.
 @param mode scanning mode, one of the:
 <table>
 <tr><td>MODE_SINGLE_SCAN</td><td>Linea will deactivate the laser after a successful barcode scan</td></tr>
 <tr><td>MODE_MULTI_SCAN</td><td>Linea will continue to scan even after successful barcode scan and will stop when scan button is released, barcodeStopScan command is sent or there is no barcode scaned for several seconds (set via call to barcodeSetScanTimeout)</td></tr>
 </table>
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)barcodeSetScanMode:(int)mode;

/**
 Enables or disables reading of specific barcode type.
 This setting is stored into the flash memory and will persists.
 @param barcodeType barcode type, one of the BAR_* constants with the exception of BAR_LAST. You can use BAR_ALL to enable or disable all barcode types at once
 @param enabled enables or disables reading of that barcode type
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)barcodeEnableBarcode:(int)barcodeType enabled:(BOOL)enabled;

/**
 Returns the current barcode type mode. See barcodeSetTypeMode for more detailed description.
 This setting will not persists.
 @return barcode type mode, one of the:
 <table>
 <tr><td>BARCODE_TYPE_DEFAULT</td><td>default barcode types, listed in BARCODES enumeration</td></tr>
 <tr><td>BARCODE_TYPE_EXTENDED</td><td>extended barcode types, listed in BARCODES_EX enumeration</td></tr>
 </table>
 @note Although this function was made for Linea 1, that had hardware button to enter sync mode, it still works for enabling/disabling automated sync on Linea 4 and onward
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(int)barcodeGetTypeMode;

/**
 Sets barcode type mode. Linea can return barcode type from the default list (listed in BARCODES)
 or extended one (listed in BARCODES_EX). The extended one is superset to the default, so current
 programs will be mostly unaffected if they switch from default to extended (with the exception of
 barcodes like UPC-A and UPC-E, which will be returned as UPC in the default list, but proper types
 in the extended. This setting will not persists.
 @param mode barcode type mode, one of the:
 <table>
 <tr><td>BARCODE_TYPE_DEFAULT (default)</td><td>default barcode types, listed in BARCODES enumeration</td></tr>
 <tr><td>BARCODE_TYPE_EXTENDED</td><td>extended barcode types, listed in BARCODES_EX enumeration</td></tr>
 </table>
 @note Although this function was made for Linea 1, that had hardware button to enter sync mode, it still works for enabling/disabling automated sync on Linea 4 and onward
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)barcodeSetTypeMode:(int)mode;

/**
 Sends data directly to the barcode engine. Use this function with EXTREME care, you can easily render
 your barcode engine useless.
 Refer to the barcode engine documentation on supported commands
 @param data command buffer
 @param length the number of bytes in data buffer
 @return TRUE if write operation succeeded
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)barcodeEngineWrite:(void *)data length:(int)length;

/**
 Sends data directly to the barcode engine. Use this function with EXTREME care, you can easily render
 your barcode engine useless.
 Refer to the barcode engine documentation on supported commands
 @param data command string
 @return TRUE if write operation succeeded
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)barcodeEngineWrite:(NSString *)data;

/**
 Reads a response from the barcode engine.
 Refer to the barcode engine documentation on supported commands
 @param data buffer, where the response will be stored
 @param length the maximum number of bytes to store in length buffer
 @param timeout the number of seconds to wait for response
 @return number of bytes actually read
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(int)barcodeEngineRead:(void *)data length:(int)length timeout:(double)timeout;

/**
 Allows basic control over the power to the barcode engine. By default Linea manages barcode engine by turning
 it on when scan operation is needed, then turning off after 5 seconds of inactivity. There are situations, where
 barcode engine should stay on to give better user experience, namely when using 2D barcode engine, which takes 1.7 seconds
 to start. This function is ignored for 1D barcode engines.
 
 <br>Be cautious using this function, if you pass TRUE to engineOn, the barcode engine will not turn off unless Linea is disconnected,
 program closes connection or iPod/iPhone goes to sleep, so it can drain the battery if left for 10+ hours on.
 This setting does not persist, it is valid for current session only.
 @param engineOn TRUE will keep the engine powered on until the function is called with FALSE. In case of FALSE, Linea will work the usual way -
 powers on the engine just before scan operation.
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(void)barcodeEnginePowerControl:(BOOL)engineOn;

/**
 Allows for a custom initialization string to be sent to the barcode. The string is sent directly, if the barcode is currently
 powered on, and every time it gets initialized. The setting does not persists, so it is best this command is called upon new connection
 with Linea
 @param data barcode engine initialization data (consult barcode engine manual)
 @return TRUE if the operation was successful
 @throw NSPortTimeoutException if there is no connection to Linea
 **/
-(BOOL)barcodeOpticonSetInitString:(NSString *)data;

/**
 Returns the current custom init string, or an empty string if none
 @throw NSPortTimeoutException if there is no connection to Linea
 **/
-(NSString *)barcodeOpticonGetInitString;

/**
 Sends configuration parameters directly to the opticon barcode engine. Use this function with EXTREME care,
 you can easily render your barcode engine useless. Refer to the barcode engine documentation on supported commands.
 <br>The function encapsulates the data with the ESC and CR so you don't have to send them. It optionally sends Z2
 after the command to ensure settings are stored in the flash.
 <br>You can send multiple parameters with a single call if you format them as follows:
 - commands that take 2 symbols can be sent without any delimiters, like: "C1C2C3"
 - commands that take 3 symbols should be prefixed by [, like: "C1[C2AC3" (in this case commands are C1, C2A and C3
 - commands that take 4 symbols should be prefixed by ], like: "C1C2]C3AB" (in this case commands are C1, C2 and C3AB
 @param data command string
 @param saveToFlash if TRUE, command also saves the settings to flash. Saving setting is slower, so should be in ideal
 case executed only once and the program to remember it. The scanner's power usually gets cut when Linea goes to sleep -
 5 seconds of idle time, so any non-stored to flash settings are lost, but if barcodeEnginePowerControl:TRUE is used on
 2D engine, then even non-saved to flash settings will persist until device disconnects (iOS goes to sleep, physical disconnect)
 @return TRUE if operation was successful
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)barcodeOpticonSetParams:(NSString *)data saveToFlash:(BOOL)saveToFlash;

/**
 Sends configuration parameters directly to the opticon barcode engine. Use this function with EXTREME care,
 you can easily render your barcode engine useless. Refer to the barcode engine documentation on supported commands.
 <br>The function encapsulates the data with the ESC and CR so you don't have to send them. It sends Z2
 after the command to ensure settings are stored in the flash.
 <br>You can send multiple parameters with a single call if you format them as follows:
 - commands that take 2 symbols can be sent without any delimiters, like: "C1C2C3"
 - commands that take 3 symbols should be prefixed by [, like: "C1[C2AC3" (in this case commands are C1, C2A and C3
 - commands that take 4 symbols should be prefixed by ], like: "C1C2]C3AB" (in this case commands are C1, C2 and C3AB
 <br>This function automatically saves the settings to flash. Saving setting is slower, so should be in ideal
 case executed only once and the program to remember it. The scanner's power usually gets cut when Linea goes to sleep -
 5 seconds of idle time, so any non-stored to flash settings are lost, but if barcodeEnginePowerControl:TRUE is used on
 2D engine, then even non-saved to flash settings will persist until device disconnects (iOS goes to sleep, physical disconnect)
 @param data command string
 @return TRUE if operation was successful
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)barcodeOpticonSetParams:(NSString *)data;

/**
 Reads barcode engine's identification
 @return opticon engine ident string
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(NSString *)barcodeOpticonGetIdent:(NSError **)error;

-(BOOL)barcodeOpticonUpdateFirmware:(NSData *)firmwareData bootLoader:(BOOL)bootLoader error:(NSError **)error;
/**@}*/



/** @defgroup G_DEP_LNCRYPTO Deprecated Cryptographic & Security Functions
 Starting from firmware 2.13, Linea provides strong cryptographic support for magnetic card data. The encryption is supported
 on all Linea devices, from software point of view they are all the same, but provide different levels of hardware/firmware security.
 
 <br>An overview of the security, provided by Linea (see each of the crypto functions for further detail):
 
 <br>Hardware/Firmware:
 
 <br>For magnetic card encryption Linea is using AES256, which is the current industry standard encryption algorithm. The encryption key
 resides in volatile, battery powered ram inside Linea's cpu (for Linea 1.5 onward) and is being lost if anyone tries to break in the
 Linea device in order to prevent the key from being stolen. Magnetic card data, along with device serial number and some random bytes
 (to ensure every packet will be different) are being sent to the iOS program in an encrypted way.
 
 
 <br>Software:
 
 <br>Currently there are 2 types of keys, that can be loaded into Linea:
 - AUTHENTICATION KEY - used for device authentication (for example the program can lock itself to work with very specific Linea device)
 and encryption of the firmware
 - ENCRYPTION KEY - used for magnetic card data encryption. To use msr encryption, you don't need to set the AUTHENTICATION KEY.
 
 <br>Keys: The keys can be set/changed in two ways:
 
 <br>1. Using plain key data - this method is easy to use, but less secure, as it relies on program running on iPod/iPhone to have the key
 inside, an attacker could compromise the system and extract the key from device's memory. Call cryptoSetKey to set the keys this way.
 If there is an existing key of the same type inside Linea, you have to pass it too.
 
 <br>2. Using encrypted key data - this method is harder to implement, but provides better security - the key data, encrypted with old key
 data is sent from a server in secure environment to the program, running on the iOS, then the program forwards it to the Linea.
 The program itself have no means to decrypt the data, so an attacker can't possibly extract the key. Refer to cryptoSetKey documentation
 for more detailed description of the loading process.
 
 <br>The initial loading of the keys should always be done in a secure environment.
 
 <br>Magnetic card encryption:
 
 <br>Once ENCRYPTION KEY is set, all magnetic card data gets encrypted, and is now sent via magneticCardEncryptedData instead. The LineaDemo
 program contains sample code to decrypt the data block and extract the contents - the serial number and track data.
 
 <br>As with keys, card data can be extracted on the iOS device itself (less secure, the application needs to have the key inside) or be sent
 to a secure server to be processed. Note, that the encrypted data contains Linea's serial number too, this can be used for Data Origin
 Verification, to be sure someone is not trying to mimic data, coming from another device.
 
 
 <br>Demo program: the sample program now have "Encryption" tab, where key management can be tested:
 
 - New AES 256 key - type in the key you want to set (or change to)
 - Old AES 256 key - type in the previous key, or leave blank if you set the key for the first time
 
 <br>[SET AUTHENTICATION KEY] and [SET ENCRYPTION KEY] buttons allow you to use the key info in the text fields above to set the key.
 
 - Decryption key - type in the key, which the demo program will use to try to decrypt card data. This field should contain the
 ENCRYPTION KEY, or something random, if you want to test failed card data decryption.
 @ingroup G_DEP_LINEA
 @{
 */

/**
 Generates 16 byte block of random numbers, required for some of the other crypto functions.
 @return 16 bytes of random numbers
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(NSData *)cryptoRawGenerateRandomData;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys
 to reside on the device, but all the operations can be execuded with data, sent from a secure server. See
 cryptoSetKey if you plan to use the key in the mobile device.
 
 <br>Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 
 <br>Generally the key loading process, using "Raw" commands, a program on the iOS device and a server which holds the keys
 will look similar to:
 
 - (iOS program) calls cryptoRawGenerateRandomData to get 16 bytes block of random data and send these to the server
 - (Server) creates byte array of 48 bytes consisting of: [RANDOM DATA: 16 bytes][KEY DATA: 32 bytes]
 - (Server) if there is current encryption key set on the Linea (if you want to change existing key) the server encrypts
 the 48 bytes block with the OLD key
 - (Server) sends the result data back to the program
 - (iOS program) calls cryptoRawSetKey with KEY_ENCRYPTION and the data it received from the server
 - (Linea) tries to decrypt the key data if there was already key present, then extracts the key, verifies the random data
 and if everything is okay, sets the key
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param encryptedData - 48 bytes that consists of 16 bytes random numbers received via call to cryptoRawGenerateRandomData
 and 32 byte AES256 key. If there has been previous key of the same type, then all 48 bytes should be encrypted with it.
 @param keyVersion - the version of the key. On firmware versions less than 2.43 this parameter is ignored and key version
 is considered to be 0x00000000. Key version is useful for the program to determine what key is inside the head.
 @param keyFlags - optional key flags, supported on ver 2.58 and onward
 - KEY_AUTHENTICATION:
 <table>
 <tr><td>BIT 1</td><td>If set to 1, scanning barcodes, reading magnetic card and using the bluetooth module are locked and have to be unlocked with cryptoAuthenticateHost/cryptoRawAuthenticateHost upon every reinsert of the device</td></tr>
 </table>
 - KEY_ENCRYPTION: No flags are supported
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoRawSetKey:(int)keyID encryptedData:(NSData *)encryptedData keyVersion:(uint32_t)keyVersion keyFlags:(uint32_t)keyFlags;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys
 to reside on the device, but all the operations can be execuded with data, sent from a secure server. See
 cryptoSetKey if you plan to use the key in the mobile device.
 
 <br>Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 
 <br>Generally the key loading process, using "Raw" commands, a program on the iOS device and a server which holds the keys
 will look similar to:
 
 - (iOS program) calls cryptoRawGenerateRandomData to get 16 bytes block of random data and send these to the server
 - (Server) creates byte array of 48 bytes consisting of: [RANDOM DATA: 16 bytes][KEY DATA: 32 bytes]
 - (Server) if there is current encryption key set on the Linea (if you want to change existing key) the server encrypts
 the 48 bytes block with the OLD key
 - (Server) sends the result data back to the program
 - (iOS program) calls cryptoRawSetKey with KEY_ENCRYPTION and the data it received from the server
 - (Linea) tries to decrypt the key data if there was already key present, then extracts the key, verifies the random data
 and if everything is okay, sets the key
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param encryptedData - 48 bytes that consists of 16 bytes random numbers received via call to cryptoRawGenerateRandomData
 and 32 byte AES256 key. If there has been previous key of the same type, then all 48 bytes should be encrypted with it.
 @param keyVersion - the version of the key. On firmware versions less than 2.43 this parameter is ignored and key version
 is considered to be 0x00000000. Key version is useful for the program to determine what key is inside the head.
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoRawSetKey:(int)keyID encryptedData:(NSData *)encryptedData keyVersion:(uint32_t)keyVersion;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys
 to reside on the device, but all the operations can be execuded with data, sent from a secure server. See
 cryptoSetKey if you plan to use the key in the mobile device.
 
 <br>Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 
 <br>Generally the key loading process, using "Raw" commands, a program on the iOS device and a server which holds the keys
 will look similar to:
 
 - (iOS program) calls cryptoRawGenerateRandomData to get 16 bytes block of random data and send these to the server
 - (Server) creates byte array of 48 bytes consisting of: [RANDOM DATA: 16 bytes][KEY DATA: 32 bytes]
 - (Server) if there is current encryption key set on the Linea (if you want to change existing key) the server encrypts
 the 48 bytes block with the OLD key
 - (Server) sends the result data back to the program
 - (iOS program) calls cryptoRawSetKey with KEY_ENCRYPTION and the data it received from the server
 - (Linea) tries to decrypt the key data if there was already key present, then extracts the key, verifies the random data
 and if everything is okay, sets the key
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param encryptedData - 48 bytes that consists of 16 bytes random numbers received via call to cryptoRawGenerateRandomData
 and 32 byte AES256 key. If there has been previous key of the same type, then all 48 bytes should be encrypted with it.
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoRawSetKey:(int)keyID encryptedData:(NSData *)encryptedData;

/**
 Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param key 32 bytes AES256 key to set
 @param oldKey 32 bytes AES256 key that was previously used, or null if there was no previous key. The old key
 should match the new key, i.e. if you are setting KEY_ENCRYPTION, then you should pass the old KEY_ENCRYPTION.
 @param keyVersion - the version of the key. On firmware versions less than 2.43 this parameter is ignored and key version
 is considered to be 0x00000000. Key version is useful for the program to determine what key is inside the head.
 @param keyFlags - optional key flags, supported on ver 2.58 and onward
 - KEY_AUTHENTICATION:
 <table>
 <tr><td>BIT 1</td><td>If set to 1, scanning barcodes, reading magnetic card and using the bluetooth module are locked and have to be unlocked with cryptoAuthenticateHost/cryptoRawAuthenticateHost upon every reinsert of the device</td></tr>
 </table>
 - KEY_ENCRYPTION: No flags are supported
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoSetKey:(int)keyID key:(NSData *)key oldKey:(NSData *)oldKey keyVersion:(uint32_t)keyVersion keyFlags:(uint32_t)keyFlags;

/**
 Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param key 32 bytes AES256 key to set
 @param oldKey 32 bytes AES256 key that was previously used, or null if there was no previous key. The old key
 should match the new key, i.e. if you are setting KEY_ENCRYPTION, then you should pass the old KEY_ENCRYPTION.
 @param keyVersion - the version of the key. On firmware versions less than 2.43 this parameter is ignored and key version
 is considered to be 0x00000000. Key version is useful for the program to determine what key is inside the head.
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoSetKey:(int)keyID key:(NSData *)key oldKey:(NSData *)oldKey keyVersion:(uint32_t)keyVersion;

/**
 Used to store AES256 keys into Linea internal memory. Valid keys that can be set:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 @param keyID the key type to set - KEY_AUTHENTICATION or KEY_ENCRYPTION
 @param key 32 bytes AES256 key to set
 @param oldKey 32 bytes AES256 key that was previously used, or null if there was no previous key. The old key
 should match the new key, i.e. if you are setting KEY_ENCRYPTION, then you should pass the old KEY_ENCRYPTION.
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoSetKey:(int)keyID key:(NSData *)key oldKey:(NSData *)oldKey;

/**
 Returns key version. Valid key ID:
 - KEY_AUTHENTICATION - if set, you can use authentication functions - cryptoRawAuthenticateDevice
 or cryptoAuthenticateDevice. Firmware updates will require authentication too
 - KEY_ENCRYPTION - if set, magnetic card data will come encrypted via magneticCardEncryptedData or
 magneticCardEncryptedRawData
 @return key version or 0xFFFFFFFF if the key version cannot be read (key versions are available in firmware 2.43 or later)
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(uint32_t)cryptoGetKeyVersion:(int)keyID;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys
 to reside on the device, but all the operations can be execuded with data, sent from a secure server. See
 cryptoAuthenticateDevice if you plan to use the key in the mobile device.
 
 <br>Encrypts a 16 bytes block of random data with the stored authentication key and returns the result.
 
 <br>The idea: if a program wants to work with specific Linea device, it sets AES256 authentication key once, then
 on every connect the program generates random 16 byte block of data, encrypts it internally with the said key,
 then encrypts it with linea too and compares the result. If that Linea contains no key, or
 the key is different, the resulting data will totally differ from the one generated.
 This does not block Linea from operation, what action will be taken if devices mismatch depends on the program.
 @param randomData 16 bytes block of data (presumably random bytes)
 @return Random data, encrypted with the Linea authentication key
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(NSData *)cryptoRawAuthenticateDevice:(NSData *)randomData;

/**
 @note Check out the cryptoRawAuthenticateDevice function, if you want to not use the key inside the mobile device.
 
 <br>Generates random data, uses the key to encrypt it, then encrypts the same data with the stored authentication key
 inside Linea and returns true if both data matches.
 Encrypts a 16 bytes block of random data with the stored authentication key and returns the result.
 
 <br>The idea: if a program wants to work with specific Linea device, it sets AES256 authentication key once, then
 on every connect the program uses cryptoAuthenticateDevice with that key. If Linea contains no key, or
 the key is different, the function will return FALSE.
 This does not block Linea from operation, what action will be taken if devices mismatch depends on the program.
 @param key 32 bytes AES256 key
 @return TRUE if Linea contains the same authentication key
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)cryptoAuthenticateDevice:(NSData *)key;

/**
 @note RAW crypto functions are harder to use and require more code, but are created to allow no secret keys
 to reside on the device, but all the operations can be execuded with data, sent from a secure server. See
 cryptoAuthenticateHost if you plan to use the key in the mobile device.
 
 <br>Tries to decrypt random data, generated from cryptoRawGenerateRandomData with the stored internal authentication
 key and returns the result. This function is used so that Linea knows a "real" device is currently connected, before
 allowing some functionality. Currently firmware update is protected by this function, once authentication key is set,
 you have to use it or cryptoAuthenticateHost before you attempt firmware update, or it will error out.
 
 <br>The idea (considering the iOS device does not have the keys inside, but depends on server):
 - (iOS program) generates random data using cryptoRawGenerateRandomData and sends to the server
 - (Server) encrypts the random data with the same AES256 key that is in the Linea and sends back to the iOS program
 - (iOS program) uses cryptoRawAuthenticateHost to authenticate with the data, an exception will be generated if authentication fails.
 @param encryptedRandomData 16 bytes block of encrypted data
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(void)cryptoRawAuthenticateHost:(NSData *)encryptedRandomData;

/**
 @note Check out the cryptoRawAuthenticateHost function, if you want to not use the key inside the mobile device.
 
 Generates random data, uses the key to encrypt it, then sends to Linea to verify against it's internal authentication
 key. If both keys match, return value is TRUE. This function is used so that Linea knows a "real" device is currently connected, before
 allowing some functionality. Currently firmware update is protected by this function, once authentication key is set,
 you have to use it or cryptoRawAuthenticateHost before you attempt firmware update, or it will error out.
 @param key 32 bytes AES256 key
 @return TRUE if Linea contains the same authentication key
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters are wrong
 */
-(BOOL)cryptoAuthenticateHost:(NSData *)key;
/**@}*/



/*******************************************************************************
 * BLUETOOTH COMMANDS
 *******************************************************************************/
/** @defgroup G_DEP_LNBLUETOOTH Deprecated Bluetooth Functions
 Functions to work with Linea's built-in bluetooth module
 @ingroup G_DEP_LINEA
 @{
 */
/**
 Returns bluethooth module status.
 @note When bluetooth module is enabled, access to the barcode engine is not possible!
 @return TRUE if bluetooth module is enabled, FALSE otherwise
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(BOOL)btGetEnabled;

/**
 Enables or disables bluetooth module. Disabling the bluetooth module is currently the way to break existing bluetooth connection.
 @note When bluetooth module is enabled, access to the barcode engine is not possible!
 @param enabled TRUE to enable the engine, FALSE to disable it
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(void)btSetEnabled:(BOOL)enabled;

/**
 Sends data to the connected remote device.
 @param data data bytes to write
 @param length the length of the data in the buffer
 @return TRUE if data was written, FALSE if failure
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(BOOL)btWrite:(void *)data length:(int)length;
-(BOOL)OEMWrite:(void *)data length:(int)length;

/**
 Sends data to the connected remote device.
 @param data data string to write
 @return TRUE if data was written, FALSE if failure
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(BOOL)btWrite:(NSString *)data;
-(BOOL)OEMWrite:(NSString *)data;

/**
 Tries to read data from the connected remote device for specified timeout.
 @param data data buffer, where the result will be stored
 @param length maximum amount of bytes to wait for
 @param timeout maximim timeout in seconds to wait for data
 @return the actual number of bytes stored in the data buffer
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(int)btRead:(void *)data length:(int)length timeout:(double)timeout;
-(int)OEMRead:(void *)data length:(int)length timeout:(double)timeout;

/**
 Tries to read string data, ending with CR/LF up to specifed timeout
 @param timeout maximim timeout in seconds to wait for data
 @return the string received or nil
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(NSString *)btReadLine:(double)timeout;

/**
 Retrieves local bluetooth name, this is the name that Linea will report to bluetooth discovery requests.
 @note this function cannot be called once connection to remote device was established
 @return bluetooth name
 @throw NSPortTimeoutException if there is no connection to Linea
 */
-(NSString *)btGetLocalName;

/**
 Performs discovery of the nearby bluetooth devices.
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param codTypes bluetooth Class Of Device to look for or 0 to search for all bluetooth devices
 @return array of strings of bluetooth addresses
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(NSArray *)btDiscoverDevices:(int)maxDevices maxTime:(double)maxTime codTypes:(int)codTypes;

/**
 Performs background discovery of the nearby bluetooth devices. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @param codTypes bluetooth Class Of Device to look for or 0 to search for all bluetooth devices
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(void)btDiscoverDevicesInBackground:(int)maxDevices maxTime:(double)maxTime codTypes:(int)codTypes;

/**
 Queries device name given the address
 @note this function cannot be called once connection to remote device was established
 @param address bluetooth address returned from btDiscoverDevices/btDiscoverPrinters
 @return bluetooth device name or nil if query failed
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(NSString *)btGetDeviceName:(NSString *)address;

/**
 Tries to connect to remote device
 @note this function cannot be called once connection to remote device was established
 @param address bluetooth address returned from btDiscoverDevices/btDiscoverPrinters
 @param pin PIN code if needed, or nil to try unencrypted connection
 @return TRUE if connection was successful, FALSE otherwise
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(BOOL)btConnect:(NSString *)address pin:(NSString *)pin;

/**
 Performs discovery of supported printers. These include PP-60, DPP-250, DPP-350, SM-112.
 @note this function cannot be called once connection to remote device was established
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @return array of strings containing bluetooth device address and bluetooth device name, i.e. if 2 printers are found, the list will contain @"address 1",@"name 1",@"address 2",@"name 2"
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(NSArray *)btDiscoverPrinters:(double)maxTime;

/**
 Performs discovery of supported printers. These include PP-60, DPP-250, DPP-350, SM-112.
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @return array of strings containing bluetooth device address and bluetooth device name, i.e. if 2 printers are found, the list will contain @"address 1",@"name 1",@"address 2",@"name 2"
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(NSArray *)btDiscoverPrinters:(int)maxDevices maxTime:(double)maxTime;

/**
 Performs background discovery of supported printers. These include PP-60, DPP-250, DPP-350, SM-112. The discovery status and devices found will be sent via delegate notifications
 @note this function cannot be called once connection to remote device was established
 @param maxDevices the maximum results to return
 @param maxTime the max time to discover, in seconds. Actual time may vary.
 @throw NSPortTimeoutException if there is no connection to Linea
 @throw NSInvalidArgumentException if some of the input parameters is wrong
 */
-(void)btDiscoverPrintersInBackground:(int)maxDevices maxTime:(double)maxTime;

/**@}*/

@end

/**@}*/

#endif