/*
     File: ChangoAU.h
 Abstract: ChangoAU.h
  Version: 1.0.1
 
 Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple
 Inc. ("Apple") in consideration of your agreement to the following
 terms, and your use, installation, modification or redistribution of
 this Apple software constitutes acceptance of these terms.  If you do
 not agree with these terms, please do not use, install, modify or
 redistribute this Apple software.
 
 In consideration of your agreement to abide by the following terms, and
 subject to these terms, Apple grants you a personal, non-exclusive
 license, under Apple's copyrights in this original Apple software (the
 "Apple Software"), to use, reproduce, modify and redistribute the Apple
 Software, with or without modifications, in source and/or binary forms;
 provided that if you redistribute the Apple Software in its entirety and
 without modifications, you must retain this notice and the following
 text and disclaimers in all such redistributions of the Apple Software.
 Neither the name, trademarks, service marks or logos of Apple Inc. may
 be used to endorse or promote products derived from the Apple Software
 without specific prior written permission from Apple.  Except as
 expressly stated in this notice, no other rights or licenses, express or
 implied, are granted by Apple herein, including but not limited to any
 patent rights that may be infringed by your derivative works or by other
 works in which the Apple Software may be incorporated.
 
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
 MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
 THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
 OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
 MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
 AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
 STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 
 Copyright (C) 2014 Apple Inc. All Rights Reserved.
 
*/

#include "AUBase.h"
#include "CAAudioChannelLayout.h"

#include <Carbon/Carbon.h>
#include <iostream>
#include <fstream>

#ifndef __ChangoAU_h__
#define __ChangoAU_h__

#include "ChangoAU.h"
#include "ChangoAUVersion.h"
#include "WaveChango.h"

#pragma mark ____ChangoAU Parameters
#define WINDOW_NAME_STR "Chango AU Plugin - Brandon Lucia 2014"
// parameters
static const float kDefaultValue_Volume = 0.2071;
static const char *dataFIFO = "/Users/blucia/CHANGO_DATA_FIFO";
static int datafd;
static float amps[25];
static pthread_t readerThread;
static pthread_mutex_t bufLock;
bool readerRun;
void *readerThreadFn(void*v);
std::ofstream changolog;

static CFStringRef kParameterVolumeName = CFSTR("Volume");
static CFStringRef kParameterOnName = CFSTR("On/Off");

enum {
	kParam_Volume =0,
	kParam_On=1,
	kNumberOfParameters=2
};

#pragma mark ____ChangoAU
class ChangoAU : public AUBase
{
public:
								ChangoAU(AudioUnit component);
	
	virtual void				Cleanup();
	
	virtual OSStatus			Initialize();

	virtual OSStatus			GetPropertyInfo(	AudioUnitPropertyID				inID,
													AudioUnitScope					inScope,
													AudioUnitElement				inElement,
													UInt32 &						outDataSize,
													Boolean &						outWritable);

	virtual OSStatus			GetProperty(	AudioUnitPropertyID 		inID,
												AudioUnitScope 				inScope,
												AudioUnitElement			inElement,
												void *						outData);
																													
	virtual	OSStatus			GetParameterInfo(	AudioUnitScope			inScope,
													AudioUnitParameterID	inParameterID,
													AudioUnitParameterInfo	&outParameterInfo);

	virtual	OSStatus 	Render(	AudioUnitRenderActionFlags &ioActionFlags,
										const AudioTimeStamp &		inTimeStamp,
										UInt32						nFrames);

	virtual bool				StreamFormatWritable(	AudioUnitScope					scope,
														AudioUnitElement				element);
	
	virtual UInt32				SupportedNumChannels(	const AUChannelInfo** 			outInfo);
																						    		
	virtual UInt32				GetChannelLayoutTags(	AudioUnitScope				scope,
														AudioUnitElement 			element,
														AudioChannelLayoutTag *		outLayoutTags);
														
	virtual UInt32				GetAudioChannelLayout(	AudioUnitScope				scope,
														AudioUnitElement 			element,
														AudioChannelLayout *		outLayoutPtr,
														Boolean &					outWritable);

	virtual OSStatus			SetAudioChannelLayout(	AudioUnitScope 				scope, 
														AudioUnitElement 			element,
														const AudioChannelLayout *	inLayout);

	virtual OSStatus			RemoveAudioChannelLayout(AudioUnitScope scope, AudioUnitElement element);
															
 	virtual	bool				SupportsTail () { return false; }
	
	/*! @method Version */
	virtual OSStatus			Version() { return kChangoAUVersion; }
	
	virtual bool				CanScheduleParameters() const { return false; }
	
private:
	
    
    CvSize fsize;
    unsigned int renderCount;
    bool inited;
    
    WaveChango *chango;
    Wave *wave;
    int pipeRead;
	
	CAAudioChannelLayout mOutputChannelLayout;
};

#endif