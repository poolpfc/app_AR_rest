
import 'dart:io';
import 'dart:convert';
import 'dart:async';

final String TEST_PROJECT_NAME = 'phonegap-layar-plugin-xcode-sample';
final String CORDOVA = 'cordova';
final String xcodeProjRelativePath = '/platforms/ios/$TEST_PROJECT_NAME.xcodeproj';

File xcodeProjFile = null;
Directory tmpDir = null;
Directory testProjectRooot = null;

final Uri script = Platform.script;
final Directory scriptDir = new Directory.fromUri(script);
final String scriptDirPath = scriptDir.path;
final String PLATFORM = 'platform';

final Uri testWwwAssetsUri = script.resolve('sample_www_assets');
final Directory testWwwAssetsDir = new Directory.fromUri(testWwwAssetsUri);

final Uri testDirUri = script.resolve('./');
final Uri scriptParent = script.resolve('../');

main(List<String> args) {

 if (args.length == 0 || args.length > 1 ) {
   stderr.writeln('Usage: dart test/run-sample.dart [ios/android]');
   exit(-1);
 }

 String platform = args[0];
 
 if (platform != 'ios' && platform != 'android') {
   stderr.writeln('Sorry the platform must be ios or android');
   exit(-1);
 }
 
 if (platform == 'ios' && !Platform.isMacOS) {
   stderr.writeln('Sorry! The iOS Sample only works on OS X.');
   exit(-1);
 }

 tmpDir = Directory.systemTemp.createTempSync('test_project_');
 print('Created tmp dir: ${tmpDir.path}');

 tmpDir = Directory.systemTemp.createTempSync('test_project_');
 print('Created tmp dir: ${tmpDir.path}');

 testProjectRooot = new Directory('${tmpDir.path}/$TEST_PROJECT_NAME');
 print('Test project`s root: ${testProjectRooot.path}');

 if (platform == 'ios') {
   xcodeProjFile = new File('${testProjectRooot.path}$xcodeProjRelativePath');
   print('XCodeProj file path: $xcodeProjFile');
   createCordovaProject().then((exitCode) => addiOSPlatforms().then((exitCode) =>
     addPlugin().then((exitCode) => openInXCode().then((exitCode) {

       print('Press any key to clean up the resources on the file-system.');
       stdin.readLineSync(encoding: UTF8, retainNewlines: true);

       print('Deleting $tmpDir recursively...');
       tmpDir.deleteSync(recursive: true);

       print('Test runner finished.');
       }))));
   } else {
    createCordovaProject().then((exitCode) => addAndroidPlatforms().then((exitCode) =>
      addPlugin().then((exitCode)  => prepareAndroidProject().then((exitCode) => runAndroidApp().then((exitCode)  {

        print('Press any key to clean up the resources on the file-system.');
        stdin.readLineSync(encoding: UTF8, retainNewlines: true);

        print('Deleting $tmpDir recursively...');
        tmpDir.deleteSync(recursive: true);

        print('Test runner finished.');
        })))));
  }
}

void checkIfBinaryIsAvailable(String binaryName) {
  ProcessResult whichNpm = Process.runSync('which', [binaryName]);
  if (whichNpm.exitCode != 0) {
    stderr.writeln('You need to have $binaryName on the path.');
    exit(-2);
  }
}

Future<int> prepareProject() {
  print('Running cordova prepare on the generated project...');
  return _runProcess(CORDOVA, ['prepare'], workingDirectory:
    testProjectRooot.path);
}

Future<int> openInXCode() {
  print('Opening generated test project in XCode.');
  return _runProcess('open', [xcodeProjFile.path], workingDirectory:
    xcodeProjFile.parent.path);
}

Future<int> runAndroidApp() {
  print('Running project in Android');
  List<String> processArgs = ['run', 'android'];
  return _runProcess(CORDOVA, processArgs, workingDirectory:
     testProjectRooot.path);
}


Future<int> addPlugin() {
  print('Adding the plugin to the generated project...');
  List<String> processArgs = ['plugin', 'add', scriptParent.path];
  return _runProcess(CORDOVA, processArgs, workingDirectory:
    testProjectRooot.path);
}

Future<int> addiOSPlatforms() {
  print('Adding platforms to the generated project...');
  List<String> processArgs = ['platform', 'add', 'ios'];
  return _runProcess(CORDOVA, processArgs, workingDirectory:
    testProjectRooot.path);
}

Future<int> addAndroidPlatforms() {
  print('Adding platforms to the generated project...');
  List<String> processArgs = ['platform', 'add', 'android'];
  return _runProcess(CORDOVA, processArgs, workingDirectory:
    testProjectRooot.path);
}

Future<int> prepareAndroidProject() {
  print('Preparing Android Project...');
  List<String> processArgs = ['prepare', 'android'];
  return _runProcess(CORDOVA, processArgs, workingDirectory:
    testProjectRooot.path);
}

Future<int> createCordovaProject() {
  print('Creating cordova project...');
  List<String> processArgs = ['create', testProjectRooot.path, 'com.phonegap.layarexample',
  TEST_PROJECT_NAME, '--link-to', testWwwAssetsDir.path];
  return _runProcess(CORDOVA, processArgs);
}

Future<int> _runProcess(String binary, List<String>
  processArgs, {workingDirectory: null}) {
  Future<Process> process = null;
  if (workingDirectory != null) {
    process = Process.start(binary, processArgs, workingDirectory:
      workingDirectory, includeParentEnvironment: true);
    } else {
      process = Process.start(binary, processArgs, workingDirectory: tmpDir.path,
        includeParentEnvironment: true);
    }

    Completer completer = new Completer();
    process.then((process) {
      process.stdout.transform(new Utf8Decoder()).transform(new LineSplitter()
        ).listen((String line) => print(line));
      process.stderr.transform(new Utf8Decoder()).transform(new LineSplitter()
        ).listen((String line) => print(line));
      process.exitCode.then((int exitCode) => completer.complete(exitCode));
      });
    return completer.future;
  }
