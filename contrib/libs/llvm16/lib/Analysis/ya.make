# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/BinaryFormat
    contrib/libs/llvm16/lib/IR
    contrib/libs/llvm16/lib/Object
    contrib/libs/llvm16/lib/ProfileData
    contrib/libs/llvm16/lib/Support
    contrib/libs/llvm16/lib/TargetParser
)

ADDINCL(
    contrib/libs/llvm16/lib/Analysis
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    AliasAnalysis.cpp
    AliasAnalysisEvaluator.cpp
    AliasAnalysisSummary.cpp
    AliasSetTracker.cpp
    Analysis.cpp
    AssumeBundleQueries.cpp
    AssumptionCache.cpp
    BasicAliasAnalysis.cpp
    BlockFrequencyInfo.cpp
    BlockFrequencyInfoImpl.cpp
    BranchProbabilityInfo.cpp
    CFG.cpp
    CFGPrinter.cpp
    CFGSCCPrinter.cpp
    CGSCCPassManager.cpp
    CallGraph.cpp
    CallGraphSCCPass.cpp
    CallPrinter.cpp
    CaptureTracking.cpp
    CmpInstAnalysis.cpp
    CodeMetrics.cpp
    ConstantFolding.cpp
    ConstraintSystem.cpp
    CostModel.cpp
    CycleAnalysis.cpp
    DDG.cpp
    DDGPrinter.cpp
    Delinearization.cpp
    DemandedBits.cpp
    DependenceAnalysis.cpp
    DependenceGraphBuilder.cpp
    DevelopmentModeInlineAdvisor.cpp
    DivergenceAnalysis.cpp
    DomPrinter.cpp
    DomTreeUpdater.cpp
    DominanceFrontier.cpp
    EHPersonalities.cpp
    FunctionPropertiesAnalysis.cpp
    GlobalsModRef.cpp
    GuardUtils.cpp
    HeatUtils.cpp
    IRSimilarityIdentifier.cpp
    IVDescriptors.cpp
    IVUsers.cpp
    ImportedFunctionsInliningStatistics.cpp
    IndirectCallPromotionAnalysis.cpp
    InlineAdvisor.cpp
    InlineCost.cpp
    InlineOrder.cpp
    InlineSizeEstimatorAnalysis.cpp
    InstCount.cpp
    InstructionPrecedenceTracking.cpp
    InstructionSimplify.cpp
    Interval.cpp
    IntervalPartition.cpp
    LazyBlockFrequencyInfo.cpp
    LazyBranchProbabilityInfo.cpp
    LazyCallGraph.cpp
    LazyValueInfo.cpp
    LegacyDivergenceAnalysis.cpp
    Lint.cpp
    Loads.cpp
    Local.cpp
    LoopAccessAnalysis.cpp
    LoopAnalysisManager.cpp
    LoopCacheAnalysis.cpp
    LoopInfo.cpp
    LoopNestAnalysis.cpp
    LoopPass.cpp
    LoopUnrollAnalyzer.cpp
    MLInlineAdvisor.cpp
    MemDepPrinter.cpp
    MemDerefPrinter.cpp
    MemoryBuiltins.cpp
    MemoryDependenceAnalysis.cpp
    MemoryLocation.cpp
    MemoryProfileInfo.cpp
    MemorySSA.cpp
    MemorySSAUpdater.cpp
    ModelUnderTrainingRunner.cpp
    ModuleDebugInfoPrinter.cpp
    ModuleSummaryAnalysis.cpp
    MustExecute.cpp
    NoInferenceModelRunner.cpp
    ObjCARCAliasAnalysis.cpp
    ObjCARCAnalysisUtils.cpp
    ObjCARCInstKind.cpp
    OptimizationRemarkEmitter.cpp
    OverflowInstAnalysis.cpp
    PHITransAddr.cpp
    PhiValues.cpp
    PostDominators.cpp
    ProfileSummaryInfo.cpp
    PtrUseVisitor.cpp
    RegionInfo.cpp
    RegionPass.cpp
    RegionPrinter.cpp
    ReplayInlineAdvisor.cpp
    ScalarEvolution.cpp
    ScalarEvolutionAliasAnalysis.cpp
    ScalarEvolutionDivision.cpp
    ScalarEvolutionNormalization.cpp
    ScopedNoAliasAA.cpp
    StackLifetime.cpp
    StackSafetyAnalysis.cpp
    SyncDependenceAnalysis.cpp
    SyntheticCountsUtils.cpp
    TFLiteUtils.cpp
    TargetLibraryInfo.cpp
    TargetTransformInfo.cpp
    TensorSpec.cpp
    Trace.cpp
    TrainingLogger.cpp
    TypeBasedAliasAnalysis.cpp
    TypeMetadataUtils.cpp
    UniformityAnalysis.cpp
    VFABIDemangling.cpp
    ValueLattice.cpp
    ValueLatticeUtils.cpp
    ValueTracking.cpp
    VectorUtils.cpp
)

END()
