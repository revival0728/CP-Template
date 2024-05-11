import kotlin.math.abs
import kotlin.math.min
import kotlin.math.max

fun readStr() = readln()
fun readStrings() = readln().split(" ")
fun readInt() = readStr().toInt()
fun readLong() = readStr().toLong()
fun readChars() = readStr().toCharArray()
fun readDouble() = readStr().toDouble()
fun readInts() = readln().split(" ").map { i -> i.toInt() }
fun readLongs() = readln().split(" ").map { i -> i.toLong() }
fun readDoubles() = readln().split(" ").map { i -> i.toDouble() }

var OUTPUT = StringBuilder()
fun out(v: Any) { OUTPUT.append(v) }
fun outLine(v: Any = "") = out("$v\n")
fun outArray(a: Array<Any>) = outLine(a.joinToString(" "))
fun outArray(a: IntArray) = outLine(a.joinToString(" "))
fun outArray(a: LongArray) = outLine(a.joinToString(" "))
fun outArray(a: BooleanArray) = outLine(a.joinToString(" "))
fun outArray(a: CharArray) = outLine(a.joinToString(" "))
fun outs(vararg v: Any) = outArray(Array(v.size) { i -> v[i] })

fun solve() {
}

fun main(args: Array<String>) {
//    val t = 1
    val t = readInt()
    for (i in 1..t) {
        solve()
    }
    print(OUTPUT.toString())
}
