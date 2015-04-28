#Check to see if version has been passed
if [ -z "$1" ]
  then
    echo "No version tag passed"
    exit 1
fi

#Get deploy script directory
SCRIPTDIR=`dirname $0`
#Build
xcodebuild -configuration Release -scheme 'Space Evaders' -project $SCRIPTDIR/Space\ Evaders.xcodeproj
#Move to src dir
cd $SCRIPTDIR/../../bin/Release
#Create DMG directory
mkdir DMG
#Copy bundle to DMG
cp -r Space\ Evaders.app DMG/.
#Add application shortcut
ln -s /Applications DMG/Applications
#Create DMG
hdiutil create -ov Space-Evaders-$1.dmg -volname "Space Evaders" -srcfolder DMG/
#Clean up DMG folder
rm -r DMG
