# Copyright (C) 2017 Beijing Didi Infinity Technology and Development Co.,Ltd.
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================

import sys
from absl import logging
from delta.data.utils.test_utils import mock_a_text_file

# samples with label
samples = ["北\tB-LOC", "京\tI-LOC", "\n\t\t", "哈\tO"]


def mock_text_class_data(train_file, dev_file, test_file):
  logging.info("Generate mock data: {}".format(train_file))
  mock_a_text_file(samples, 1000, train_file)
  logging.info("Generate mock data: {}".format(dev_file))
  mock_a_text_file(samples, 100, dev_file)
  logging.info("Generate mock data: {}".format(test_file))
  mock_a_text_file(samples, 100, test_file)


if __name__ == '__main__':
  logging.set_verbosity(logging.INFO)

  if len(sys.argv) != 4:
    logging.error("Usage python {} train_file, dev_file, test_file".format(sys.argv[0]))
    sys.exit(-1)

  train_file = sys.argv[1]
  dev_file = sys.argv[2]
  test_file = sys.argv[3]

  mock_text_class_data(train_file, dev_file, test_file)
