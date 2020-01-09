#
# project
#
project(SOlib)

# Include "/lib" directory
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})


#
# Add subfolders
#
add_subdirectory(utils)
add_subdirectory(base)
add_subdirectory(deetc)
add_subdirectory(toronto)
add_subdirectory(itc2007)



#
# Set public header list (add your headers and source files here))
#
set(${PROJECT_NAME}_headers
        # lib/base/algorithms
        base/algorithms/moGDA.h
        base/algorithms/moGDAexplorer.h
        base/algorithms/moSA.h
        base/algorithms/moSAexplorer.h
        base/algorithms/moSimpleCoolingSchedule.h
        base/algorithms/moTA.h
        base/algorithms/moTAexplorer.h
        # lib/base/algorithms/statistics
        base/algorithms/statistics/moTAWithStatistics.h
        base/algorithms/statistics/moTAexplorerWithStatistics.h
        # lib/base/chromosome
        base/chromosome/Chromosome.h
        base/chromosome/ChromosomeCapacitated.hpp
        base/chromosome/eoChromosome.h
        base/chromosome/eoChromosomeCapacitated.hpp
        base/chromosome/eoExtendedChromosome.h
        base/chromosome/ExtendedChromosome.h
        # lib/base/neighbourhood
        base/neighbourhood/ETTPneighbor.h
        base/neighbourhood/ETTPneighborEval.h
        base/neighbourhood/ETTPneighborhood.h
        # lib/base/kempeChain
        base/kempeChain/ETTPKempeChainHeuristic.h
        base/kempeChain/ETTPKempeChainHeuristicTwoEpoch.h
        base/kempeChain/ETTPKempeChain.h
        # lib/base/kempeChain/statistics
        base/kempeChain/statistics/ETTPKempeChainHeuristicWithStatistics.h
        # lib/base/statistics
        base/statistics/ExamInfo.h
        base/statistics/ExamMoveStatistics.h
        # lib/base
        base/Common.h
        #lib/toronto
        #
        # lib
        Crossover.h
        Constraint.hpp
        ConstraintValidator.hpp
        CSVParser.h
        Data.h
        DateTime.h
        DEETCTestSet.h
        eoCellularEA.h
        eoCellularEARing.h
        eoCellularEAMatrix.h
        eoETTPEval.h
        eoETTPNumberClashesEval.h
        eoEvolutionOperator.h
        eoGenerationContinue.h
        eoSCEA.h
        eoSCEAConstrained.h
        eoSimpleGA.h
        ETTPInit.h
        Exam.h
        GraphColouringHeuristics.h
        GraphColouringHeuristics_ITC2007_CHANGED_9_FEB_2015.h
        ITC2007Constraints.hpp
        ITC2007Period.h
        ITC2007SolutionInitialiser.h
        ITC2007TestSet.h
        Matrix.h
        Mutation.h
        Period.h
        ProximityCostEval.h
        Room.h
        TestSet.h
        TestSetDescription.h
        TimetableProblemData.hpp
        TorontoTestSet.h
        VertexPriorityQueue.h
)

set(${PROJECT_NAME}_sources
        # lib/base/
        # lib/base/chromosome
        base/chromosome/Chromosome.cpp
        base/chromosome/ChromosomeCapacitated.cpp
        base/chromosome/eoChromosome.cpp
        base/chromosome/eoChromosomeCapacitated.cpp
        base/chromosome/eoExtendedChromosome.cpp
        base/chromosome/ExtendedChromosome.cpp
        # lib/toronto
        toronto/MainAppTorontoDatasets.cpp
        # lib/utils
        utils/Utils.cpp
        # lib/base/statistics
        base/statistics/ExamInfo.cpp
        base/statistics/ExamMoveStatistics.cpp
        # lib/deetc
        deetc/MainApp2EpochDEETC.cpp
        # lib
        Crossover.cpp
        DateTime.cpp
        DEETCTestSet.cpp
        GraphColouringHeuristics.cpp
        ITC2007TestSet.cpp
        MainApp.cpp
        Matrix.cpp
        Mutation.cpp
        TestSetDescription.cpp
        TorontoTestSet.cpp
        VertexPriorityQueue.cpp
)



add_library(SOlib SHARED ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})


# Include ParadisEO, Boost Regex, Armadillo, ncurses5-dev libs
#target_link_libraries(${PROJECT_NAME} boost_regex eo es moeo cma eoutils ga armadillo ncurses)
target_link_libraries(${PROJECT_NAME} boost_regex eo es moeo cma eoutils ga armadillo)



