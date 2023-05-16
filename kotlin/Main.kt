import functionSolving.*

fun main(args: Array<String>) {
    val problem = LeetCodeProblem { solution, problemParams ->
        val (s, t) = getStringParams(problemParams)
        solution.minWindow(s, t)
    }
    problem.addCase(""""BANC"""", "String", """"ADOBECODEBANC"""", "String", """"ABC"""")
    problem.addCase(""""a"""", "String", """"a"""", "String", """"a"""")
    problem.addCase("", "String", """"a"""", "String", """"aa"""")
    problem.runTests()
}