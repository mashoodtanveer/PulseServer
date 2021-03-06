///////////////////////////////////////////////////////////////////////////////////////
///////// > openSMILE configuration file for data output <           //////////////////
/////////                                                            //////////////////
///////// (c) audEERING GmbH,                                        //////////////////
/////////     All rights reserverd.                                  //////////////////
///////////////////////////////////////////////////////////////////////////////////////


/*
   This file can be included as data output file for standard feature
   extraction configuration files. It provides commandline options
   for the batch extraction GUI, and supports LLD and Functionals (summaries)
   saving.

   It requires the main extrator configuration file to provide the following
   data memory levels:  lld, lld_de, and func
 */

  //////////////////////////////////////////////////////////////////////
 ///////////////////  data output configuration  //////////////////////
//////////////////////////////////////////////////////////////////////

;;;;;;;;; output LLD features to CSV ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[componentInstances:cComponentManager]
instance[lldsink].type=cCsvSink
instance[lldhtksink].type=cHtkSink
instance[arffsink].type=cArffSink
instance[csvsink].type=cCsvSink
instance[htksink].type=cHtkSink

[lldsink:cCsvSink]
reader.dmLevel = lld;lld_de
filename=\cm[lldoutput(D){?}:output csv file for LLD, disabled by default ?, only written if filename given]
instanceName=\cm[instname(N){unknown}:instance name]
append = \cm[appendlld{0}:set to 1 to append to the LLD output csv file, default is not to append]
timestamp = 1
number = 0
printHeader = 1
errorOnNoOutput = 1

[lldhtksink:cHtkSink]
reader.dmLevel = lld;lld_de
filename=\cm[lldhtkoutput(D){?}:output HTK binary file for LLD, disabled by default ?, only written if filename given]
append = \cm[appendhtklld{0}:set to 1 to append to the LLD output htk file, default is not to append]
  ; this is broken for HTK sink...
errorOnNoOutput = 0  
parmKind = 9

[arffsink:cArffSink]
reader.dmLevel=func
frameIndex = 0
frameTime = 0
filename=\cm[output(O){?}:name of WEKA Arff output file, set to a valid filename to enable this output sink]
relation=\cm[relation{openSMILE_features}:arff relation attribute, feature set name and/or corpus name]
instanceName=\cm[instname]
 ;; use this line instead of the above to always set the instance name to the
 ;; name of the input wave file
 ;instanceName=\cm[inputfile]
\{\cm[arfftargetsfile{arff_targets.conf.inc}:name of arff targets include file]}
append=\cm[appendstaticarff{1}:set to 0 to disable appending to an existing arff parameter summary file, given by the arffoutput option]
errorOnNoOutput = 1

[csvsink:cCsvSink]
reader.dmLevel = func
filename=\cm[csvoutput{?}:output CSV file for summarised parameters, set to a valid filename to enable this output sink, data is appended if file exists]
append=\cm[appendstaticcsv{1}:set to 0 to disable appending to an existing csv parameter summary file, given by the csvoutput option]
frameIndex=0
frameTime=0
instanceName=\cm[instname]
errorOnNoOutput = 1

  ; TODO: output without a frame period does not work so that HTK (HList) can read it!
[htksink:cHtkSink]
reader.dmLevel = func
filename=\cm[htkoutput{?}:output HTK file for summarised parameters, set to a valid filename to enable this output sink, no append by default, use -appendstatichtk option to enable]
append=\cm[appendstatichtk{0}:set to 1 to enable appending to an existing HTK parameter summary file, given by the htkoutput option]
parmKind = 9
  ; this is broken for HTK sink...
errorOnNoOutput = 0
 ; avoid broken files which HTK cannot read for period approx. > 0.06 (int16 overflow)
forcePeriod = 0.01

