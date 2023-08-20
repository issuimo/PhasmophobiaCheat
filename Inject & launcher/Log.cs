using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Inject___launcher {
    internal class Log {
        public static string FormatLog(string doc) {
            return "[" + System.DateTime.Now.ToString("mm:ss") + "] " +doc ;
        }
    }
}
