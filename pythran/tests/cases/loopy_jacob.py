#pythran export loopy(int list list, int, int, int)
#runas data = [[1, 45, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0], [0, 60, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0]] ; loopy(data, 0, 100, 100)
#skip.bench data = [[1, 45, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0]] + [[0, 60, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0]] * 200 ; loopy(data, 0, 100, 100) TOO_SLOW
def _WarningErrorHandler(msg,fatal, _WarningCount):
    if _WarningCount > 200:
        raise RuntimeError(msg)
    else:
        return _WarningCount +1

def loopy(_PopulationSetInfo_Data, _WarningCount, _NumberOfTriesToGenerateThisIndividual, _NumberOfTriesToGenerateThisSimulationStep):
    #### Functions Allowed in Expressions ####
    IndividualID = 0
    Repetition = 0
    Time = 0
    _ResultsInfo_Data = []
    #### Create State Handler Functions and State Classification Vector ##### 
    ############### Execute Simulation ###############
    ####### Subject Loop #######
    _Subject = 0
    while _Subject < (len(_PopulationSetInfo_Data)):
        IndividualID = IndividualID +1
        # Comment/Uncomment the next line to disable/enable printing of verbose information
        #print "Simulating Individual #" + str(IndividualID)
        _NumberOfTriesToGenerateThisIndividual = 1
        ##### Repetition Loop #####
        Repetition = 0
        while Repetition < (1000):
            # Reset repeat individual repetition flag in case it was set
            _RepeatSameIndividualRepetition = False
            #Init all parameters - Resetting them to zero
            # Comment/Uncomment the next line to disable/enable printing of verbose information
            #print "  Repetition = " + str(Repetition)
            Gender, Age, State0, State1, State2, State3Terminal, Example_6___Main_Process, Example_6___Main_Process_Entered, State0_Entered, State1_Entered, State2_Entered, State3Terminal_Entered = 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            # Init parameters from population set
            [Gender, Age, State0, State1, State2, State3Terminal, Example_6___Main_Process, Example_6___Main_Process_Entered, State0_Entered, State1_Entered, State2_Entered, State3Terminal_Entered] = _PopulationSetInfo_Data[IndividualID-1]
            # Init parameters from Initialization Phase
            # Reset time and load first vector into results
            Time = 0
            # Load the initial condition into the results vector for this individual
            _ResultsInfoForThisIndividual = [ [IndividualID, Repetition, Time ,Gender, Age, State0, State1, State2, State3Terminal, Example_6___Main_Process, Example_6___Main_Process_Entered, State0_Entered, State1_Entered, State2_Entered, State3Terminal_Entered] ]
            _Terminate_Time_Loop = False or State3Terminal != 0
            _NumberOfTriesToGenerateThisSimulationStep = 0
            _RepeatSameSimulationStep = False
            ##### Time Loop #####
            while Time < 3:
                if _RepeatSameSimulationStep:
                    # if repeating the same simulation step, reset the flag to avoid infinite loops
                    _RepeatSameSimulationStep = False
                    # Load the previous time step results into the results vector for this individual
                    [_IgnoreIndividualID, _IgnoreRepetition, _IgnoreTime ,Gender, Age, State0, State1, State2, State3Terminal, Example_6___Main_Process, Example_6___Main_Process_Entered, State0_Entered, State1_Entered, State2_Entered, State3Terminal_Entered] = _ResultsInfoForThisIndividual[-1]
                    _Terminate_Time_Loop = False
                elif _Terminate_Time_Loop:
                    # If the time loop has to be terminated
                    break
                else:
                    # If not repeating the same simulation step, nor terminating, increase the time counter
                    Time = Time + 1
                # Comment/Uncomment the next line to disable/enable printing of verbose information
                #print "    Time Step = " + str(Time)
                # Reset Warning/Error Count
                _WarningCountBeforeThisSimulationStep = _WarningCount
                # Increase the number of Tries counter
                _NumberOfTriesToGenerateThisSimulationStep = _NumberOfTriesToGenerateThisSimulationStep + 1
                ##### Phase 1 - Pre State Transition #####
                # Processing the rule: "Affected Parameter: Age; Simulation Phase: Pre-stateOccurrence Probability: 1; Applied Formula: Age +1; Rule Notes: Age Increase; ; 
                _LastExpressionString = "Processing the expression: _Threshold = 1 ."
                # This expression should expand to: _Threshold = 1
                try:
                    # Building Step #0: _Threshold = 1
                    _Temp = 1
                    if not (-1e-14 <= _Temp  <= 1.00000000000001):
                        _WarningCount = _WarningErrorHandler("The occurrence probability threshold defined by a rule does not evaluate to a number between 0 and 1 within a tolerance specified by the system option parameter SystemPrecisionForProbabilityBoundCheck. The occurrence probability was evaluated to: " + str(_Temp) + " for the rule: " + 'Affected Parameter: Age; Simulation Phase: Pre-stateOccurrence Probability: 1; Applied Formula: Age +1; Rule Notes: Age Increase; ; ', True, _WarningCount) 
                except:
                    _WarningCount = _WarningErrorHandler(_LastExpressionString, True, _WarningCount)
                # Expression building complete - assign to destination parameter 
                _Threshold = _Temp
                if  0.5 < _Threshold:
                    _LastExpressionString = "Processing the expression: Age = Age +1 ."
                    # This expression should expand to: Age = Age +1
                    try:
                        # Building Step #0: Age = Age
                        _Temp0 = Age
                        # Building Step #1: Age = Age +1
                        _Temp = _Temp0 +1
                    except:
                        _WarningCount = _WarningErrorHandler(_LastExpressionString, True, _WarningCount)
                    # Expression building complete - assign to destination parameter 
                    Age = _Temp
                    pass
                ##### End of Rule Processing #####
                ##### Error Handlers #####
                if _WarningCount <= _WarningCountBeforeThisSimulationStep:
                    # Load New results to the results vector
                    _ResultsInfoForThisIndividual.append([IndividualID, Repetition, Time ,Gender, Age, State0, State1, State2, State3Terminal, Example_6___Main_Process, Example_6___Main_Process_Entered, State0_Entered, State1_Entered, State2_Entered, State3Terminal_Entered])
                    _NumberOfTriesToGenerateThisSimulationStep = 0
                else:
                    #print "    Repeating the same simulation step due to an error - probably a bad validity check"
                    _RepeatSameSimulationStep = True
                    if _NumberOfTriesToGenerateThisSimulationStep >= 5:
                        if _NumberOfTriesToGenerateThisIndividual < 2:
                            # Repeat the calculations for this person
                            _RepeatSameIndividualRepetition = True 
                            break
                        else:
                            _WarningCount = _WarningErrorHandler("The simulation was halted since the number of tries to recalculate the same person has been exceeded. If this problem consistently repeats itself, check the formulas to see if these cause too many out of bounds numbers to be generated. Alternatively, try raising the system option NumberOfTriesToRecalculateSimulationOfIndividualFromStart which is now defined as 2  .  ", True, _WarningCount)
            if _RepeatSameIndividualRepetition:
                #print "  Repeating the same repetition for the same individual due to exceeding the allowed number of simulation steps recalculations for this individual"
                _NumberOfTriesToGenerateThisIndividual = _NumberOfTriesToGenerateThisIndividual + 1
            else:
                # If going to the next individual repetition, save the results and increase the counter
                # Load New results to the results vector
                _ResultsInfo_Data.extend(_ResultsInfoForThisIndividual)
                Repetition = Repetition + 1
        _Subject = _Subject + 1
    # Comment/Uncomment the next lines to disable/enable dumping output file
    return _ResultsInfo_Data

