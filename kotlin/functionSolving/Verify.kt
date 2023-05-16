package functionSolving

fun accepted() = println("Accepted")
fun wrongAnswer(myAnswer: String) = println("Wrong Answer, Your Answer: $myAnswer")

fun prettierToString(obj: Any?): String {
    if(obj is String)
        return obj
    if(obj is Int)
        return "$obj"
    if(obj is Long)
        return "$obj"
    if(obj is Float)
        return "$obj"
    if(obj is Double)
        return "$obj"
    if(obj is Boolean)
        return "${if(obj) 1 else 0}"
    if(obj is IntArray)
        return "[${obj.joinToString(",") { prettierToString(it) }}]"
    if(obj is LongArray)
        return "[${obj.joinToString(",") { prettierToString(it) }}]"
    if(obj is DoubleArray)
        return "[${obj.joinToString(",") { prettierToString(it) }}]"
    if(obj is FloatArray)
        return "[${obj.joinToString(",") { prettierToString(it) }}]"
    if(obj is BooleanArray)
        return "[${obj.joinToString(",") { prettierToString(it) }}]"
    if(obj is Array<*>)
        return "[${obj.joinToString(",") { prettierToString(it) }}]"
    return "Undefined Method"
}

fun checker(a: Any?, b: Any?) {
    fun compare(a: Any?, b: Any?): Boolean {
        if(a === b)
            return true
        if(a is IntArray && b is IntArray) {
            if(a.size != b.size)
                return false
            for(i in a.indices)
                if(a[i] != b[i])
                    return false
            return true
        }
        if(a is LongArray && b is LongArray) {
            if(a.size != b.size)
                return false
            for(i in a.indices)
                if(a[i] != b[i])
                    return false
            return true
        }
        if(a is BooleanArray && b is BooleanArray) {
            if(a.size != b.size)
                return false
            for(i in a.indices)
                if(a[i] != b[i])
                    return false
            return true
        }
        if(a is FloatArray && b is FloatArray) {
            if(a.size != b.size)
                return false
            for(i in a.indices)
                if(a[i] != b[i])
                    return false
            return true
        }
        if(a is DoubleArray && b is DoubleArray) {
            if(a.size != b.size)
                return false
            for(i in a.indices)
                if(a[i] != b[i])
                    return false
            return true
        }
        if(a is Array<*> && b is Array<*>) {
            if(a.size != b.size)
                return false
            var ret = true
            for(i in a.indices)
                ret = ret and compare(a[i], b[i])
            return ret
        }
        return (a == b)
    }
    if(compare(a, b)) {
        accepted()
    } else {
        wrongAnswer(prettierToString(a))
    }
}

fun make2DIntArray(n: Int, m: Int, vararg v: Int): Array<IntArray> {
    val ret = Array(n) { IntArray(m) { 0 } }
    for(i in 0 until n) {
        for(j in 0 until m) {
            ret[i][j] = v[i * m + j]
        }
    }
    return ret
}

enum class ProblemParamType {
    Int, Double, Float, String, Boolean, Long, Null,
    IntArray, LongArray, FloatArray, DoubleArray, StringArray, BooleanArray,
    IntArray2D, LongArray2D, FloatArray2D, DoubleArray2D, BooleanArray2D,
}
abstract class ProblemParam(val paramType: ProblemParamType)
data class NullParam(val param: Boolean = true) : ProblemParam(ProblemParamType.Null)
data class IntParam(val param: Int) : ProblemParam(ProblemParamType.Int)
data class FloatParam(val param: Float) : ProblemParam(ProblemParamType.Float)
data class DoubleParam(val param: Double) : ProblemParam(ProblemParamType.Double)
data class StringParam(val param: String) : ProblemParam(ProblemParamType.String)
data class BooleanParam(val param: Boolean) : ProblemParam(ProblemParamType.Boolean)
data class LongParam(val param: Long) : ProblemParam(ProblemParamType.Long)
data class IntArrayParam(val param: IntArray) : ProblemParam(ProblemParamType.IntArray)
data class FloatArrayParam(val param: FloatArray) : ProblemParam(ProblemParamType.FloatArray)
data class DoubleArrayParam(val param: DoubleArray) : ProblemParam(ProblemParamType.DoubleArray)
data class LongArrayParam(val param: LongArray) : ProblemParam(ProblemParamType.LongArray)
data class BooleanArrayParam(val param: BooleanArray) : ProblemParam(ProblemParamType.BooleanArray)
data class StringArrayParam(val param: Array<String>) : ProblemParam(ProblemParamType.StringArray)
data class IntArray2DParam(val param: Array<IntArray>) : ProblemParam(ProblemParamType.IntArray2D)
data class BooleanArray2DParam(val param: Array<BooleanArray>) : ProblemParam(ProblemParamType.BooleanArray2D)
data class FloatArray2DParam(val param: Array<FloatArray>) : ProblemParam(ProblemParamType.FloatArray2D)
data class DoubleArray2DParam(val param: Array<DoubleArray>) : ProblemParam(ProblemParamType.DoubleArray2D)
data class LongArray2DParam(val param: Array<LongArray>) : ProblemParam(ProblemParamType.LongArray2D)

inline fun <reified ParamType> getParams(problemParams: Array<ProblemParam>) : List<ParamType> =
    problemParams.filterIsInstance<ParamType>().map { it }
fun getIntParams(problemParams: Array<ProblemParam>): List<Int> = getParams<IntParam>(problemParams).map { it.param }
fun getIntArrayParams(problemParams: Array<ProblemParam>): List<IntArray> = getParams<IntArrayParam>(problemParams).map { it.param }
fun getIntArray2DParams(problemParams: Array<ProblemParam>): List<Array<IntArray>> = getParams<IntArray2DParam>(problemParams).map { it.param }
fun getStringParams(problemParams: Array<ProblemParam>): List<String> = getParams<StringParam>(problemParams).map { it.param }
fun getStringArrayParams(problemParams: Array<ProblemParam>): List<Array<String>> = getParams<StringArrayParam>(problemParams).map { it.param }

class LeetCodeProblem<AnswerType>(private val runner: (Solution, Array<ProblemParam>) -> AnswerType) {
    private val cases = ArrayList<Array<ProblemParam>>()
    private val answers = ArrayList<String>()
    private fun parseArray(p: String): List<String> = p.slice(1 until p.length - 1).split(",")
    private fun parse2DArray(p: String): List<List<String>> = p.slice(1 until p.length - 1).split(",").map { parseArray(it) }
    fun addCase(ans: String, vararg problemParameters: String) {
        cases.add(Array<ProblemParam>(problemParameters.size / 2) { NullParam() })
        answers.add(ans)
        val types = problemParameters.filterIndexed { index, _ ->  (index and 1) == 0 }
        val values = problemParameters.filterIndexed { index, _ ->  (index and 1) != 0 }
        for(i in 0 until problemParameters.size / 2) {
            cases.last()[i] = (when(types[i]) {
                "Int" -> IntParam(values[i].toInt())
                "Long" -> LongParam(values[i].toLong())
                "Float" -> FloatParam(values[i].toFloat())
                "Double" -> DoubleParam(values[i].toDouble())
                "Boolean" -> BooleanParam(values[i].toBoolean())
                "String" -> StringParam(values[i].slice(1 until values[i].length))
                "IntArray" -> IntArrayParam(parseArray(values[i]).map { it.toInt() }.toIntArray())
                "IntArray2D" -> IntArray2DParam(parse2DArray(values[i]).map { it.map { subIt -> subIt.toInt() }.toIntArray() }.toTypedArray())
                "LongArray" -> LongArrayParam(parseArray(values[i]).map { it.toLong() }.toLongArray())
                "LongArray2D" -> LongArray2DParam(parse2DArray(values[i]).map { it.map { subIt -> subIt.toLong() }.toLongArray() }.toTypedArray())
                "FloatArray" -> FloatArrayParam(parseArray(values[i]).map { it.toFloat() }.toFloatArray())
                "FloatArray2D" -> FloatArray2DParam(parse2DArray(values[i]).map { it.map { subIt -> subIt.toFloat() }.toFloatArray() }.toTypedArray())
                "DoubleArray" -> DoubleArrayParam(parseArray(values[i]).map { it.toDouble() }.toDoubleArray())
                "DoubleArray2D" -> DoubleArray2DParam(parse2DArray(values[i]).map { it.map { subIt -> subIt.toDouble() }.toDoubleArray() }.toTypedArray())
                "BooleanArray" -> BooleanArrayParam(parseArray(values[i]).map { it.toBoolean() }.toBooleanArray())
                "BooleanArray2D" -> BooleanArray2DParam(parse2DArray(values[i]).map { it.map { subIt -> subIt.toBoolean() }.toBooleanArray() }.toTypedArray())
                "StringArray" -> StringArrayParam(parseArray(values[i]).toTypedArray())
                else -> NullParam()
            })
        }
    }
    fun runTests() {
        for(i in answers.indices) {
            print("Case #${i + 1}: ")
            checker(prettierToString(runner(Solution(), cases[i])), answers[i])
        }
    }
}