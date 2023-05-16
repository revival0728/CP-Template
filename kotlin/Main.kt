import functionSolving.getIntParams
import functionSolving.getIntArrayParams
import functionSolving.Solution
import functionSolving.LeetCodeProblem

fun main(args: Array<String>) {
    val problem = LeetCodeProblem { solution, problemParams ->
        val (target) = getIntParams(problemParams)
        val (nums) = getIntArrayParams(problemParams)
        solution.twoSum(nums, target)
    }
    problem.addCase("[0,1]", "IntArray", "[2,7,11,15]", "Int", "9")
    problem.runTests()
}