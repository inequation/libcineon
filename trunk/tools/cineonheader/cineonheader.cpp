// -*- mode: C++; tab-width: 4 -*-
// vi: ts=4

/*
 * Copyright (c) 2010, Patrick Palmer and Leszek Godlewski.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Patrick Palmer nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <iostream>
#include <sstream>
#include <string>


#include "Cineon.h"


using namespace std;
using namespace cineon;




void Usage()
{
	cout << "usage: dpxheader [-xX] file.dpx" << endl;
	cout << "       -x xml format" << endl;
	cout << "       -X xml format without declaration line" << endl;
}


string XmlTag(const string str)
{
	string r;
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		char ch = tolower(str[i]);
		if (ch == ' ')
			ch = '_';
		r += ch;
	}
	return r;
}


bool sub = false;

void StartSub(const string t, const int num, const bool xml)
{
	sub = true;
	if (xml)
	{
		cout << "  <" << XmlTag(t);
		if (num >= 0)
			cout << " id=\"" << num << "\"";
		cout << ">" << endl;
	}
	else
	{
		cout << t;
		if (num >= 0)
			cout << "# " << num;
		cout << endl;
	}
}


void EndSub(const string t, const bool xml)
{
	sub = false;
	if (xml)
	{
		cout << "  </" << XmlTag(t) << ">" << endl;
	}
}


void Output(const string t, const string v, const bool xml)
{
	if (sub)
		cout << "  ";

	if (xml)
	{
		cout << "  <" << XmlTag(t) << ">" << v << "</" << XmlTag(t) << ">" << endl;
	}
	else
	{
		cout << t << ": " << v << endl;
	}
}



void Output(const string t, const R32 v, const bool xml)
{
	ostringstream o;
	o << v;
	Output(t, o.str(), xml);
}


void Output(const string t, const U16 v, const bool xml)
{
	ostringstream o;
	o << v;
	Output(t, o.str(), xml);
}


void StrOutput(const string t, const string v, const int len, const bool xml)
{
	char buf[256];
	::strncpy(buf, v.c_str(), len);
	buf[len] = '\0';

	if (sub)
		cout << "  ";

	if (xml)
	{
		cout << "  <" << XmlTag(t) << ">" << buf << "</" << XmlTag(t) << ">" << endl;
	}
	else
	{
		cout << t << ": " << buf << endl;
	}
}





string Display(U8 d)
{
	if (d == 0xff)
		return "0xff";
	else
	{
		ostringstream o;
		o << U16(d);
		return o.str();
	}
}


string Display(U16 d)
{
	if (d == 0xffff)
		return "0xffff";
	else
	{
		ostringstream o;
		o << d;
		return o.str();
	}
}


string Display(U32 d)
{
	if (d == 0xffffffff)
		return "0xffffffff";
	else
	{
		ostringstream o;
		o << d;
		return o.str();
	}
}


string Display(S32 d)
{
	if (d == 0xffffffff)
		return "0xffffffff";
	else
	{
		ostringstream o;
		o << d;
		return o.str();
	}
}


string Display(R32 d)
{
	if (d == 0xffffffff)
		return "0xffffffff";
	else
	{
		ostringstream o;
		o << d;
		return o.str();
	}
}

string DisplayOrientation(U32 o)
{
	string s;

	switch (o)
	{
	case kLeftToRightTopToBottom:
		s = "Left to Right Top To Bottom";
		break;
	case kRightToLeftTopToBottom:
		s = "Right to Left Top To Bottom";
		break;
	case kLeftToRightBottomToTop:
		s = "Left to Right Bottom To Top";
		break;
	case kRightToLeftBottomToTop:
		s = "Right To Left Bottom to Top";
		break;
	case kTopToBottomLeftToRight:
		s = "Top To Bottom Left to Right";
		break;
	case kTopToBottomRightToLeft:
		s = "Top To Bottom Right to Left";
		break;
	case kBottomToTopLeftToRight:
		s = "Bottom to Top Left to Right";
		break;
	case kBottomToTopRightToLeft:
		s = "Bottom to Top Right to Left";
		break;
	case kUndefinedOrientation:
		s = "Undefined";
		break;
	default:
		s = "Unknown " + Display(o);
	}

	return s;
}


string DisplayPacking(U8 p)
{
	string s;

	switch (p)
	{
	case kPacked:
		s = "Packed";
		break;
	case kByteLeft:
		s = "8-bit boundary, left justified";
		break;
	case kByteRight:
		s = "8-bit boundary, right justified";
		break;
	case kWordLeft:
		s = "16-bit boundary, left justified";
		break;
	case kWordRight:
		s = "16-bit boundary, right justified";
		break;
	case kLongWordLeft:
		s = "32-bit boundary, left justified";
		break;
	case kLongWordRight:
		s = "32-bit boundary, right justified";
		break;
	default:
		s = "Unknown " + Display(p);
	}

	return s;
}



string DisplayInterleave(U8 i)
{
	string s;

	switch (i)
	{
	case kPixel:
		s = "Pixel";
		break;
	case kLine:
		s = "Line";
		break;
	case kChannel:
		s = "Channel (planar)";
		break;
	default:
		s = "Unknown " + Display(i);
	}

	return s;
}



string DisplayDescriptor(U8 d)
{
	string s;

	switch (d)
	{
	case cineon::kGrayscale:
		s = "Grayscale";
		break;
	case cineon::kPrintingDensityRed:
		s = "Red, printing density";
		break;
	case cineon::kRec709Red:
		s = "Red, Rec709";
		break;
	case cineon::kPrintingDensityGreen:
		s = "Green, printing density";
		break;
	case cineon::kRec709Green:
		s = "Green, Rec709";
		break;
	case cineon::kPrintingDensityBlue:
		s = "Blue, printing density";
		break;
	case cineon::kRec709Blue:
		s = "Blue, Rec709";
		break;
	case kUndefinedDescriptor:
		s = "Undefined";
		break;
	default:
		s = "Unknown " + Display(d);
		break;
	}

	return s;
}



int main(int argc, char **argv)
{
	bool xml = false;
	bool xmlDeclaration = false;
	int findx = 1;
	char buf[24];

	// check argument count
	if (argc == 3)
	{
		if (strcmp("-x", argv[1]) == 0)
		{
			findx = 2;
			xml = true;
			xmlDeclaration = true;
		}
		else if (strcmp("-X", argv[1]) == 0)
		{
			findx = 2;
			xml = true;
		}
		else
		{
			Usage();
			return 1;
		}
	}
	else if (argc != 2)
	{
		Usage();
		return 1;
	}

	// open the image
	InStream img;
	if (!img.Open(argv[findx]))
	{
		cout << "Unable to open file " << argv[findx] << endl;
		return 1;
	}

	cineon::Header header;

	if (!header.Read(&img))
	{
		cout << "Unable to read header" << endl;
		return 1;
	}


	// display header info
	if (xml)
	{
		if (xmlDeclaration)
			cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << endl;
		cout << "<cineon>" << endl;
	}

	char str[201];
	header.Version(str);
	StrOutput("Version",str, 8, xml);

	::sprintf(buf, "%x", header.MagicNumber());
	StrOutput("Magic Number", buf, 8, xml);
	StrOutput("Endian Swap", (header.RequiresByteSwap() ? "true" : "false"), 6, xml);
	Output("Image Offset", Display(header.ImageOffset()), xml);
	Output("Generic Size", Display(header.GenericSize()), xml);
	Output("Industry Size", Display(header.IndustrySize()), xml);
	Output("User Size", Display(header.UserSize()), xml);
	Output("File Size", Display(header.FileSize()), xml);

	header.FileName(str);
	StrOutput("Filename", str, 100, xml);
	header.CreationDate(str);
	StrOutput("Creation Date", str, 12, xml);
	header.CreationTime(str);
	StrOutput("Creation Time", str, 12, xml);

	Output("Image Orientation", DisplayOrientation(header.ImageOrientation()), xml);
	Output("Number of Elements", (U16)header.NumberOfElements(), xml);

	for (int i = 0; i < header.numberOfElements; i++)
	{
		StartSub("Image Element", (i+1), xml);
		StrOutput("Metric", (header.Metric(i) == 0 ? "universal" : "" + header.Metric(i)), 10, xml);
		Output("Descriptor", DisplayDescriptor(header.ImageDescriptor(i)), xml);
		Output("Bit Size", Display(header.BitDepth(i)), xml);
		Output("Width", Display(header.PixelsPerLine(i)), xml);
		Output("Height", Display(header.LinesPerElement(i)), xml);
		Output("Low Data", Display(header.LowData(i)), xml);
		Output("Low Quantity", Display(header.LowQuantity(i)), xml);
		Output("High Data", Display(header.HighData(i)), xml);
		Output("High Quantity", Display(header.chan[i].highQuantity), xml);
		EndSub("Image Element", xml);
	}

	float coords[2];
	header.WhitePoint(coords);
	Output("White Point X", Display(coords[0]), xml);
	Output("White Point Y", Display(coords[1]), xml);
	header.RedPrimary(coords);
	Output("Red Primary X", Display(coords[0]), xml);
	Output("Red Primary Y", Display(coords[1]), xml);
	header.GreenPrimary(coords);
	Output("Green Primary X", Display(coords[0]), xml);
	Output("Green Primary Y", Display(coords[1]), xml);
	header.BluePrimary(coords);
	Output("Blue Primary X", Display(coords[0]), xml);
	Output("Blue Primary Y", Display(coords[1]), xml);
	header.LabelText(str);
	StrOutput("Label Text", str, 200, xml);
	Output("Interleave", DisplayInterleave(header.ImageInterleave()), xml);
	Output("Packing", DisplayPacking(header.ImagePacking()), xml);
	Output("Data Sign", Display(header.DataSign()), xml);
	Output("End of Line Padding", Display(header.EndOfLinePadding()), xml);
	Output("End of Image Padding", Display(header.EndOfImagePadding()), xml);

	Output("X Offset", Display(header.XOffset()), xml);
	Output("Y Offset", Display(header.YOffset()) , xml);
	header.SourceImageFileName(str);
	StrOutput("Source Image Filename", str, 100, xml);
	header.SourceDate(str);
	StrOutput("Source Date", str, 12, xml);
	header.SourceTime(str);
	StrOutput("Source Time", str, 12, xml);
	header.InputDevice(str);
	StrOutput("Input Device", str, 64, xml);
	header.InputDeviceModelNumber(str);
	StrOutput("Input Device Model Number", str, 32, xml);
	header.InputDeviceSerialNumber(str);
	StrOutput("Input Device Serial Number", str, 32, xml);
	Output("X Device Pitch", Display(header.XDevicePitch()), xml);
	Output("Y Device Pitch", Display(header.YDevicePitch()), xml);
	Output("Gamma", Display(header.Gamma()), xml);

	header.FilmEdgeCode(buf);
	StrOutput("Film Code", buf, 16, xml);

	header.Format(str);
	StrOutput("Format", str, 32, xml);
	Output("Frame Position", Display(header.FramePosition()), xml);
	Output("Frame Rate", Display(header.FrameRate()), xml);
	header.FrameId(str);
	StrOutput("Frame Id", str, 32, xml);
	header.SlateInfo(str);
	StrOutput("Slate Info", str, 100, xml);

	if (xml)
		cout << "</cineon>" << endl;

	return 0;
}

