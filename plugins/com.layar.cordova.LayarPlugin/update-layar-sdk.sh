#!/bin/bash

MY_PATH=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

echo "Fetching Layar iOS and Android SDK used in phonegap plugin from sdk.layar.com"

HTML_DOWNLOAD_PAGE=$(wget -O - -o /dev/null http://sdk.layar.com/downloads)
IOS_SDK=$(echo "$HTML_DOWNLOAD_PAGE" | grep "ios_latest" | python -c "import sys, re;print re.findall(r'<a id=\'ios_latest\' href=\'(.*?)\'>', sys.stdin.read())[0]")
ANDROID_SDK=$(echo "$HTML_DOWNLOAD_PAGE" | grep "android_latest" | python -c "import sys, re;print re.findall(r'<a id=\'android_latest\' href=\'(.*?)\'>', sys.stdin.read())[0]")

IOS_SDK_URL="http://sdk.layar.com/downloads/$IOS_SDK"
echo "Downloading iOS SDK From $IOS_SDK_URL"

ANDROID_SDK_URL="http://sdk.layar.com/downloads/$ANDROID_SDK"
echo "Downloading Android SDK From $ANDROID_SDK_URL"

TEMP_DIR=`mktemp -d -t download-phonegap`           && \
echo "Created Temporary Directory: $dir"            && \
cd $TEMP_DIR                                        && \

mkdir ios                                           && \
cd ios                                              && \
curl -sS $IOS_SDK_URL > ios_sdk.zip                 && \
unzip ios_sdk.zip -d "$MY_PATH"/src/ios/SDK         && \
rm ios_sdk.zip                                      && \
cd ..

mkdir android                                       && \
cd android                                          && \
curl -sS $ANDROID_SDK_URL > android_sdk.zip         && \
unzip android_sdk.zip -d "$MY_PATH"/src/android/SDK && \
rm android_sdk.zip                                  && \
cd ..

cd $MY_PATH
rm -rf $TEMP_DIR
