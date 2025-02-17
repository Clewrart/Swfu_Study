document.addEventListener('DOMContentLoaded', function () {
    let charts = null;

    function loadParkNumbers() {
        $.ajax({
            url: '/get_distinct_parknum',
            type: 'GET',
            success: function (data) {
                if (data.status === "success") {
                    let html = '<option value="all">全部</option>';
                    data.parknums.forEach(item => {
                        html += `<option value="${item.parknum}">${item.parknum}</option>`;
                    });
                    $('#park_num').html(html);

                    if (!charts) {
                        charts = initCharts();
                    }
                }
            },
            error: function (error) {
                console.error('获取车场号失败:', error);
            }
        });
    }

    const parkColors = {
        colors: [
            '#85d29f',
            '#1585ff',
            '#ff7c7c',
            '#ffd572',
            '#9d9eff',
            '#ff9d6f',
            '#75e6da',
            '#845ec2'
        ]
    };



    function initCharts() {
        var hourlyChart = echarts.init(document.getElementById('echart2'));

        var hourlyOption = {
            title: {
                text: '预约时段分布',
                left: 'center'
            },
            tooltip: {
                trigger: 'axis',
                axisPointer: {
                    type: 'cross'
                },
                formatter: function (params) {
                    let result = params[0].name + '<br/>';
                    params.sort((a, b) => b.value - a.value);
                    params.forEach(param => {
                        let marker = `<span style="display:inline-block;margin-right:5px;border-radius:50%;width:10px;height:10px;background-color:${param.color};"></span>`;
                        result += `${marker}${param.seriesName}: ${param.value}件预约<br/>`;
                    });
                    return result;
                }
            },
            legend: {
                type: 'scroll',
                orient: 'horizontal',
                top: 25,
                right: 20,
                data: []
            },
            grid: {
                left: '3%',
                right: '4%',
                bottom: '3%',
                containLabel: true
            },
            xAxis: {
                type: 'category',
                boundaryGap: false,
                data: Array.from({ length: 24 }, (_, i) => `${String(i).padStart(2, '0')}:00`),
                axisLine: {
                    lineStyle: {
                        color: '#666'
                    }
                },
                axisLabel: {
                    interval: 2
                }
            },
            yAxis: {
                type: 'value',
                name: '预约数量',
                splitLine: {
                    lineStyle: {
                        type: 'dashed'
                    }
                }
            },
            series: [],
            dataZoom: [{
                type: 'inside',
                start: 0,
                end: 100
            }]
        };

        var rateOption = {
            title: {
                text: '预约成功率',
                left: 'center'
            },
            tooltip: {
                trigger: 'item',
                formatter: '{b}: {c} ({d}%)'
            },
            legend: {
                type: 'scroll',
                orient: 'vertical',
                right: 10,
                top: 'middle'
            },
            series: [
                {
                    type: 'pie',
                    radius: ['50%', '70%'],
                    center: ['40%', '50%'],
                    avoidLabelOverlap: false,
                    itemStyle: {
                        borderRadius: 10,
                        borderColor: '#fff',
                        borderWidth: 2
                    },
                    label: {
                        show: false
                    },
                    emphasis: {
                        label: {
                            show: true,
                            fontSize: '16',
                            fontWeight: 'bold'
                        }
                    },
                    data: []
                }
            ]
        };

        hourlyChart.setOption(hourlyOption);

        function updateCharts(parknum = 'all') {
            const timeDimension = $('#time_dimension').val();
            let xAxisData = [];
            if (timeDimension === 'week') {
                xAxisData = ['周一', '周二', '周三', '周四', '周五', '周六', '周日'];

                hourlyOption.xAxis.data = xAxisData;
                hourlyOption.xAxis.axisLabel.interval = 0; 
            } else if (timeDimension === 'month') {
                xAxisData = Array.from({ length: 31 }, (_, i) => `${i + 1}日`);

                hourlyOption.xAxis.data = xAxisData;
                hourlyOption.xAxis.axisLabel.interval = 2; 
            } else if (timeDimension === 'year') {
                xAxisData = Array.from({ length: 12 }, (_, i) => `${i + 1}月`);

                hourlyOption.xAxis.data = xAxisData;
                hourlyOption.xAxis.axisLabel.interval = 0; 
            }
            else {
                xAxisData = Array.from({ length: 24 }, (_, i) => `${String(i).padStart(2, '0')}:00`);
            }


            $.ajax({
                url: '/api/reservation/stats',
                type: 'GET',
                data: {
                    parknum: parknum,
                    time_dimension: timeDimension
                },
                success: function (response) {
                    if (response.status === 'success') {
                        const data = response.data;

                        let hourlySeries = [];

                        if (parknum === 'all') {
                            Object.entries(data.hourly).forEach(([parkNum, hourlyData], index) => {
                                hourlySeries.push({
                                    name: `车场${parkNum}`,
                                    type: 'line',
                                    smooth: true,
                                    symbol: 'circle',
                                    symbolSize: 8,
                                    sampling: 'average',
                                    data: hourlyData,
                                    itemStyle: {
                                        color: parkColors.colors[index % parkColors.colors.length]
                                    },
                                    lineStyle: {
                                        width: 2
                                    },
                                    emphasis: {
                                        focus: 'series',
                                        symbolSize: 10
                                    }
                                });
                            });
                        } else {
                            const hourlyData = data.hourly[parknum];
                            if (hourlyData) {
                                hourlySeries = [{
                                    name: `车场${parknum}`,
                                    type: 'line',
                                    smooth: true,
                                    symbol: 'circle',
                                    symbolSize: 8,
                                    sampling: 'average',
                                    data: hourlyData,
                                    itemStyle: {
                                        color: parkColors.colors[0]
                                    },
                                    lineStyle: {
                                        width: 2
                                    },
                                    emphasis: {
                                        focus: 'series',
                                        symbolSize: 10
                                    }
                                }];
                            }
                        }


                        hourlyChart.setOption({
                            title: {
                                text: '预约时段分布',
                                left: 'center'
                            },
                            tooltip: {
                                trigger: 'axis',
                                axisPointer: {
                                    type: 'cross'
                                },
                                formatter: function (params) {
                                    let result = params[0].name + '<br/>';
                                    params.sort((a, b) => b.value - a.value);
                                    params.forEach(param => {
                                        let marker = `<span style="display:inline-block;margin-right:5px;border-radius:50%;width:10px;height:10px;background-color:${param.color};"></span>`;
                                        result += `${marker}${param.seriesName}: ${param.value}件预约<br/>`;
                                    });
                                    return result;
                                }
                            },
                            legend: {
                                type: 'scroll',
                                orient: 'horizontal',
                                top: 25,
                                right: 20,
                                data: hourlySeries.map(series => series.name)
                            },
                            grid: {
                                left: '3%',
                                right: '4%',
                                bottom: '3%',
                                containLabel: true
                            },
                            xAxis: {
                                type: 'category',
                                boundaryGap: false,
                                data: xAxisData,
                                axisLine: {
                                    lineStyle: {
                                        color: '#666'
                                    }
                                },
                                axisLabel: {
                                    interval: 2
                                }
                            },
                            yAxis: {
                                type: 'value',
                                name: '预约数量',
                                splitLine: {
                                    lineStyle: {
                                        type: 'dashed'
                                    }
                                }
                            },
                            series: hourlySeries,
                            dataZoom: [{
                                type: 'inside',
                                start: 0,
                                end: 100
                            }]
                        }, true);

                    }
                },
                error: function (err) {
                    console.error('获取数据失败:', err);
                }
            });
        }

        updateCharts();

        $('#park_num').on('change', function () {
            updateCharts($(this).val());
        });

        $('#time_dimension').on('change', function () {
            updateCharts($('#park_num').val());
        });

        $('.nav-tabs a').on('click', function (e) {
            e.preventDefault();

            $('.nav-tabs a').removeClass('active');
            $(this).addClass('active');

            const timeRange = $(this).data('range');
            currentTimeRange = timeRange;
            if (charts) {
                charts.updateCharts($('#park_num').val(), timeRange);
            }
        });
        setInterval(() => updateCharts($('#park_num').val()), 5 * 60 * 1000);

        window.addEventListener('resize', function () {
            hourlyChart.resize();
        });

        return {
            hourlyChart,
            updateCharts
        };
    }

    loadParkNumbers();
});